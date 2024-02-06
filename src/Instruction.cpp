#include "../include/Instruction.h"

Instruction::Instruction(unsigned short opcode, const Cpu& c8_cpu, const Memory& ch8_memory, const Display& ch8_display)
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
            if (opcode_ & 0xF == 0x0)
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
    std::cout << "Instruction '" << opcode_ << "' undefined...\n";
}

void Instruction::CLS() {

}

void Instruction::RET() {

}

void Instruction::JP_ADDR() {

}

void Instruction::CALL_ADDR() {

}

void Instruction::SE_VX_KK() {

}
void Instruction::SNE_VX_KK() {

}

void Instruction::SE_VX_VY() {

}

void Instruction::LD_VX_KK() {

}

void Instruction::ADD_VX_KK() {

}

void Instruction::LD_VX_VY() {

}

void Instruction::OR_VX_VY(){

}

void Instruction::AND_VX_VY() {

}

void Instruction::XOR_VX_VY() {

}

void Instruction::ADD_VX_VY() {

}

void Instruction::SUB_VX_VY() {

}

void Instruction::SHR_VX() {

}

void Instruction::SUBN_VX_VY() {

}

void Instruction::SHL_VX() {

}

void Instruction::SNE_VX_VY() {

}

void Instruction::LD_I_ADDR() {

}

void Instruction::RND_VX_KK() {

}

void Instruction::JP_V0_ADDR() {

}

void Instruction::DRW_VX_VY_N() {

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

}

void Instruction::LD_F_VX() {

}

void Instruction::LD_B_VX() {

}

void Instruction::LD_I_VX() {

}

void Instruction::LD_VX_I() {

}