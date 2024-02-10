#include "../include/Instruction.h"

Instruction::Instruction(uint16_t opcode, Cpu& c8_cpu, Memory& ch8_memory, 
                         Display& ch8_display, Keyboard& ch8_keyboard)
  : opcode_ {opcode}
  , cpu_ {c8_cpu}
  , memory_ {ch8_memory}
  , display_ {ch8_display}
  , keyboard_ {ch8_keyboard} {
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
    // printf("Executing: 0x%4x | pc @ %d\n", opcode_, cpu_.pc);
    (this->*instruction_)();
}

void Instruction::UndefinedInstruction() {
    std::cout << "Instruction Undefined...\n";
}

void Instruction::CLS() {
    display_.Clear();
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
    cpu_.V[0xF] = 0;
}

void Instruction::AND_VX_VY() {
    cpu_.V[X_()] &= cpu_.V[Y_()];
    cpu_.V[0xF] = 0;
}

void Instruction::XOR_VX_VY() {
    cpu_.V[X_()] ^= cpu_.V[Y_()];
    cpu_.V[0xF] = 0;
}

void Instruction::ADD_VX_VY() {
    // TODO: Test this casting
    uint16_t res {static_cast<uint16_t>(cpu_.V[X_()] + cpu_.V[Y_()])};
    cpu_.V[X_()] = res & (0xFF);
    cpu_.V[0xF]  = (res > 255) ? 1 : 0;
}

void Instruction::SUB_VX_VY() {
    bool not_borrow = cpu_.V[X_()] >= cpu_.V[Y_()];
    cpu_.V[X_()] = cpu_.V[X_()] - cpu_.V[Y_()];
    // VF = NOT borrow
    cpu_.V[0xF] = static_cast<bool>(not_borrow);
}

void Instruction::SHR_VX() {
    // TODO: Rename this function
    cpu_.V[X_()] = cpu_.V[Y_()];
    uint8_t lsb {static_cast<uint8_t>(cpu_.V[X_()] & 0x1)};
    cpu_.V[X_()] >>= 1;
    // If LSB is 1 then VF = 1, else VF = 0
    cpu_.V[0xF] = lsb;
}

void Instruction::SUBN_VX_VY() {
    bool not_borrow = cpu_.V[X_()] <= cpu_.V[Y_()];
    cpu_.V[X_()] = cpu_.V[Y_()] - cpu_.V[X_()];
    // VF = NOT borrow
    cpu_.V[0xF] = static_cast<bool>(not_borrow);
}

void Instruction::SHL_VX() {
    // TODO: Rename this function
    cpu_.V[X_()] = cpu_.V[Y_()];
    uint8_t msb {static_cast<uint8_t>(cpu_.V[X_()] >> 7)};
    cpu_.V[X_()] <<= 1;
    // If MSB is 1 then VF = 1, else VF = 0
    cpu_.V[0xF] = msb;
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
    uint8_t x {static_cast<uint8_t>(cpu_.V[X_()] % 64)};
    uint8_t y {static_cast<uint8_t>(cpu_.V[Y_()] % 32)};
    uint16_t height {N_()};

    cpu_.V[0xF] = 0;
    for (int row = 0; row < height; ++row) {
        if (y+row >= Display::kRawHeight)
            break;

        uint16_t sprite_byte {memory_[cpu_.I + row]};
        std::bitset<8> pixels = {sprite_byte};
        for (int bit = 0; bit < 8; ++bit) {
            if (x+bit >= Display::kRawWidth)
                break;

            if (pixels[7-bit] == 1 && display_.Coordinate(x+bit, y+row) == 1) {
                display_.Coordinate(x+bit, y+row) = 0;
                cpu_.V[0xF] = 1;
            } else if (pixels[7-bit] == 1) {
                display_.Coordinate(x+bit, y+row) = 1;
            }
        }
    }

    display_.Draw();
}

void Instruction::SKP_VX() {
    if (keyboard_.IsPressed(cpu_.V[X_()]))
        cpu_.pc += 2;
}

void Instruction::SKNP_VX() {
    if (!keyboard_.IsPressed(cpu_.V[X_()]))
        cpu_.pc += 2;
}

void Instruction::LD_VX_DT() {
    cpu_.V[X_()] = cpu_.t_delay;
}

void Instruction::LD_VX_K() {
    // Wait for key press
    uint8_t *keypress_ptr {nullptr};
    while (keypress_ptr == nullptr) {
        SDL_Event event {};
        if(SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                keypress_ptr = keyboard_.CheckInput(event.key.keysym.scancode, true);
                break;
            case SDL_QUIT:
                SDL_PushEvent(&event);
                return;
            default:
                break;
            }
        }
    }

    // Wait for key release
    uint8_t *keyrelease_ptr {nullptr};
    while (keyrelease_ptr != keypress_ptr) {
        SDL_Event event {};
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYUP:
                keyrelease_ptr = keyboard_.CheckInput(event.key.keysym.scancode, false);
            case SDL_QUIT:
                SDL_PushEvent(&event);
                return;
            default:
                break;
        }
    }

    // This operation gives us the index of the key that was pressed in the list (0x0 - 0xF)
    cpu_.V[X_()] = static_cast<uint8_t>(keypress_ptr - &keyboard_[0]);
}

void Instruction::LD_DT_VX() {
    cpu_.t_delay = cpu_.V[X_()];
}

void Instruction::LD_ST_VX() {
    cpu_.t_sound = cpu_.V[X_()];
}

void Instruction::ADD_I_VX() {
    cpu_.I += cpu_.V[X_()];
}

void Instruction::LD_F_VX() {
    cpu_.I = 5*(cpu_.V[X_()]);
}

void Instruction::LD_B_VX() {
    // TODO: Verify this
    uint16_t num = cpu_.V[X_()];
    memory_[cpu_.I] = num / 100;            // Get hundreds place
    memory_[cpu_.I + 1] = (num % 100) / 10; // Get tens place
    memory_[cpu_.I + 2] = (num % 10);       // Get ones place
}

void Instruction::LD_I_VX() {
    for (int i = 0; i <= X_(); ++i) {
        memory_[cpu_.I++] = cpu_.V[i];
    }
}

void Instruction::LD_VX_I() {
    for (int i = 0; i <= X_(); ++i) {
        cpu_.V[i] = memory_[cpu_.I++];
    }
}