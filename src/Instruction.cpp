#include "../include/Instruction.h"

Instruction::Instruction(uint16_t opcode, Cpu& c8_cpu, Memory& ch8_memory, Display& ch8_display)
  : opcode_ {opcode}
  , cpu_ {c8_cpu}
  , memory_ {ch8_memory}
  , display_ {ch8_display} {
    // Parse opcode
    switch (opcode_ & 0xF000) {
        case 0x0000:
            switch (opcode_ & 0x00FF) {
                case 0xE0:
                    instruction_ = &Instruction::CLS;
                    break;
                case 0xEE:
                    instruction_ = &Instruction::RET;
                    break;
            }
            break;
        case 0x1000:
            instruction_ = &Instruction::JP_ADDR;
            break;
        case 0x2000:
            instruction_ = &Instruction::CALL_ADDR;
            break;
        case 0x3000:
            instruction_ = &Instruction::SE_VX_KK;
            break;
        case 0x4000:
            instruction_ = &Instruction::SNE_VX_KK;
            break;
        case 0x5000:
            instruction_ = &Instruction::SE_VX_VY;
            break;
        case 0x6000:
            instruction_ = &Instruction::LD_VX_KK;
            break;
        case 0x7000:
            instruction_ = &Instruction::ADD_VX_KK;
            break;
        case 0x8000:
            switch (opcode_ & 0xF) {
                case 0x0:
                    instruction_ = &Instruction::LD_VX_VY;
                    break;
                case 0x1:
                    instruction_ = &Instruction::OR_VX_VY;
                    break;
                case 0x2:
                    instruction_ = &Instruction::AND_VX_VY;
                    break;
                case 0x3:
                    instruction_ = &Instruction::XOR_VX_VY;
                    break;
                case 0x4:
                    instruction_ = &Instruction::ADD_VX_VY;
                    break;
                case 0x5:
                    instruction_ = &Instruction::SUB_VX_VY;
                    break;
                case 0x6:
                    instruction_ = &Instruction::SHR_VX;
                    break;
                case 0x7:
                    instruction_ = &Instruction::SUBN_VX_VY;
                    break;
                case 0xE:
                    instruction_ = &Instruction::SHL_VX;
                    break;
            }
            break;
        case 0x9000:
            if ((opcode_ & 0xF) == 0x0)
                instruction_ = &Instruction::SNE_VX_VY;
            break;
        case 0xA000:
            instruction_ = &Instruction::LD_I_ADDR;
            break;
        case 0xB000:
            instruction_ = &Instruction::JP_V0_ADDR;
            break;
        case 0xC000:
            instruction_ = &Instruction::RND_VX_KK;
            break;
        case 0xD000:
            instruction_ = &Instruction::DRW_VX_VY_N;
            break;
        case 0xE000:
            switch (opcode_ & 0xFF) {
                case 0x9E:
                    instruction_ = &Instruction::SKP_VX;
                    break;
                case 0xA1:
                    instruction_ = &Instruction::SKNP_VX;
                    break;
            }
            break;
        case 0xF000:
            switch(opcode_ & 0xFF) {
                case 0x07:
                    instruction_ = &Instruction::LD_VX_DT;
                    break;
                case 0x0A:
                    instruction_ = &Instruction::LD_VX_K;
                    break;
                case 0x15:
                    instruction_ = &Instruction::LD_DT_VX;
                    break;
                case 0x18:
                    instruction_ = &Instruction::LD_ST_VX;
                    break;
                case 0x1E:
                    instruction_ = &Instruction::ADD_I_VX;
                    break;
                case 0x29:
                    instruction_ = &Instruction::LD_F_VX;
                    break;
                case 0x33:
                    instruction_ = &Instruction::LD_B_VX;
                    break;
                case 0x55:
                    instruction_ = &Instruction::LD_I_VX;
                    break;
                case 0x65:
                    instruction_ = &Instruction::LD_VX_I;
                    break;
            }
            break;
    }

}

void Instruction::Execute() {
    std::cout << "Executing instruction: '" << opcode_ << "'\n";
    (this->*instruction_)();
}

void Instruction::UndefinedInstruction() {
    //TODO: Maybe throw exception to be caught further up?
    std::cout << "Instruction '" <<  opcode_ << "' undefined...\n";
}

void Instruction::CLS() {
    for (auto& pixel : display_.Screen()) {
        // Clear pixel
        pixel = 0;
    }
    
    display_.Draw();
}

void Instruction::RET() {
    if (cpu_.sp == 0) {
        // TODO: Handle with an exception?
        std::cout << "Error in RET. Stack point out of bounds\n";
        return;
    }

    // Set program counter to addr at top of stack
    cpu_.pc = cpu_.stack[cpu_.sp - 1];

    --cpu_.sp;
}

void Instruction::JP_ADDR() {
    cpu_.pc = ADDR_();
}

void Instruction::CALL_ADDR() {
    cpu_.stack[cpu_.sp] = cpu_.pc;
    ++cpu_.sp;
    cpu_.pc = ADDR_();
}

void Instruction::SE_VX_KK() {
    if (cpu_.V[X_()] == KK_())
        cpu_.pc += 2;
}
void Instruction::SNE_VX_KK() {
    if (cpu_.V[X_()] != KK_())
        cpu_.pc += 2;
}

void Instruction::SE_VX_VY() {
    if (cpu_.V[X_()] == cpu_.V[Y_()])
        cpu_.pc += 2;
}

void Instruction::LD_VX_KK() {
    cpu_.V[X_()] = KK_();
}

void Instruction::ADD_VX_KK() {
    cpu_.V[X_()] += KK_();
}

void Instruction::LD_VX_VY() {
    cpu_.V[X_()] = cpu_.V[Y_()];
}

void Instruction::OR_VX_VY(){
    cpu_.V[X_()] |= cpu_.V[Y_()];
}

void Instruction::AND_VX_VY() {
    cpu_.V[X_()] &= cpu_.V[Y_()];
}

void Instruction::XOR_VX_VY() {
    cpu_.V[X_()] ^= cpu_.V[Y_()];
}

void Instruction::ADD_VX_VY() {
    // TODO: Test this casting
    uint16_t res { static_cast<uint16_t>(cpu_.V[X_()] +  cpu_.V[Y_()])};
    if (res > 255)
        cpu_.V[0xF] = 1;
    cpu_.V[X_()] = res & (0xFF);
}

void Instruction::SUB_VX_VY() {
    // VF = NOT borrow
    if (cpu_.V[X_()] > cpu_.V[Y_()])  // If we don't need to borrow
        cpu_.V[0xF] = 1;
    else
        cpu_.V[0xF] = 0;

    cpu_.V[X_()] = cpu_.V[X_()] - cpu_.V[Y_()];
}

void Instruction::SHR_VX() {
    // If LSB is 1 then VF = 1, else VF = 0
    cpu_.V[0xF] = 0 | (cpu_.V[X_()] & 0x1);
    cpu_.V[X_()] /= 2;
}

void Instruction::SUBN_VX_VY() {
    // VF = NOT borrow
    if (cpu_.V[X_()] < cpu_.V[Y_()])  // If we don't need to borrow
        cpu_.V[0xF] = 1;
    else
        cpu_.V[0xF] = 0;

    cpu_.V[X_()] = cpu_.V[Y_()] - cpu_.V[X_()];
}

void Instruction::SHL_VX() {
    // If MSB is 1 then VF = 1, else VF = 0
    cpu_.V[0xF] = 0 | (cpu_.V[X_()] & 0x80);
    cpu_.V[X_()] *= 2;
}

void Instruction::SNE_VX_VY() {
    if (cpu_.V[X_()] != cpu_.V[Y_()])
        cpu_.pc += 2;
}

void Instruction::LD_I_ADDR() {
    cpu_.I = ADDR_();
}

void Instruction::JP_V0_ADDR() {
    cpu_.pc = cpu_.V[0x0] + ADDR_();
}


void Instruction::RND_VX_KK() {
    // TODO: Implement real randomization
    cpu_.V[X_()] = (rand() % 256) & KK_();
}

void Instruction::DRW_VX_VY_N() {
    unsigned short x = cpu_.V[X_()];
    unsigned short y = cpu_.V[Y_()];
    unsigned short height = N_();
    unsigned short pixel = 0;

    cpu_.V[0xF] = 0;

    for (int i = 0; i < height; i++) {
        pixel = memory_[cpu_.I + i];
        for (int j = 0; j < 8; j++) {
            if ((pixel & (0x80 >> j)) != 0 && (x + j + (y + i) * 64)) {
                if (display_[(x + j + ((y + i) * 64)) % (64 * 32)] == 1) {
                    // Collision
                    cpu_.V[0xF] = 1;
                }
                display_[x + j + ((y + i) * 64)] ^= 1;
            }
        }
    }

    display_.Draw();
}

void Instruction::SKP_VX() {
    
}

void Instruction::SKNP_VX() {

}

void Instruction::LD_VX_DT() {

}

void Instruction::LD_VX_K() {

}

void Instruction::LD_DT_VX() {

}

void Instruction::LD_ST_VX() {

}

void Instruction::ADD_I_VX() {
    cpu_.I += cpu_.V[X_()];
}

void Instruction::LD_F_VX() {
    //cpu_.I = 0x000 + 5*(cpu_.V[X_()]);
}

void Instruction::LD_B_VX() {
    // TODO: Verify this
    uint16_t num = cpu_.V[X_()];
    memory_[cpu_.I] = num / 100;            // Get hundreds place
    memory_[cpu_.I + 1] = (num % 100) / 10; // Get tens place
    memory_[cpu_.I + 2] = (num % 10);       // Get ones place
}

void Instruction::LD_I_VX() {
    for (int i = 0; i < X_(); ++i) {
        memory_[cpu_.I + i] = cpu_.V[i];
    }
}

void Instruction::LD_VX_I() {
    for (int i = 0; i < X_(); ++i) {
        cpu_.V[i] = memory_[cpu_.I + i];
    }
}