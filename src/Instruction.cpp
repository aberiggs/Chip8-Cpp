#include "../include/Instruction.h"

Instruction::Instruction(unsigned short opcode, Cpu& c8_cpu, Memory& ch8_memory, Display& ch8_display)
  : opcode_ {opcode}
  , cpu_ {c8_cpu}
  , memory_ {ch8_memory}
  , display_ {ch8_display} {
    // Parse opcode
    switch (opcode_ & 0xF000) {
        case 0x0000:
            switch (opcode_ & 0x00FF) {
                case 0xE0:
                    instruction_ = CLS;
                    break;
                case 0xEE:
                    instruction_ = RET;
                    break;
            }
            break;
        case 0x1000:
            instruction_ = JP_ADDR;
            break;
        case 0x2000:
            instruction_ = CALL_ADDR;
            break;
        case 0x3000:
            instruction_ = SE_VX_KK;
            break;
        case 0x4000:
            instruction_ = SNE_VX_KK;
            break;
        case 0x5000:
            instruction_ = SE_VX_VY;
            break;
        case 0x6000:
            instruction_ = LD_VX_KK;
            break;
        case 0x7000:
            instruction_ = ADD_VX_KK;
            break;
        case 0x8000:
            switch (opcode_ & 0xF) {
                case 0x0:
                    instruction_ = LD_VX_VY;
                    break;
                case 0x1:
                    instruction_ = OR_VX_VY;
                    break;
                case 0x2:
                    instruction_ = AND_VX_VY;
                    break;
                case 0x3:
                    instruction_ = XOR_VX_VY;
                    break;
                case 0x4:
                    instruction_ = ADD_VX_VY;
                    break;
                case 0x5:
                    instruction_ = SUB_VX_VY;
                    break;
                case 0x6:
                    instruction_ = SHR_VX;
                    break;
                case 0x7:
                    instruction_ = SUBN_VX_VY;
                    break;
                case 0xE:
                    instruction_ = SHL_VX;
                    break;
            }
            break;
        case 0x9000:
            if (opcode_ & 0xF == 0x0)
                instruction_ = SNE_VX_VY;
            break;
        case 0xA000:
            instruction_ = LD_I_ADDR;
            break;
        case 0xB000:
            instruction_ = JP_V0_ADDR;
            break;
        case 0xC000:
            instruction_ = RND_VX_KK;
            break;
        case 0xD000:
            instruction_ = DRW_VX_VY_N;
            break;
        case 0xE000:
            switch (opcode_ & 0xFF) {
                case 0x9E:
                    instruction_ = SKP_VX;
                    break;
                case 0xA1:
                    instruction_ = SKNP_VX;
                    break;
            }
            break;
        case 0xF000:
            switch(opcode_ & 0xFF) {
                case 0x07:
                    instruction_ = LD_VX_DT;
                    break;
                case 0x0A:
                    instruction_ = LD_VX_K;
                    break;
                case 0x15:
                    instruction_ = LD_DT_VX;
                    break;
                case 0x18:
                    instruction_ = LD_ST_VX;
                    break;
                case 0x1E:
                    instruction_ = ADD_I_VX;
                    break;
                case 0x29:
                    instruction_ = LD_F_VX;
                    break;
                case 0x33:
                    instruction_ = LD_B_VX;
                    break;
                case 0x55:
                    instruction_ = LD_I_VX;
                    break;
                case 0x65:
                    instruction_ = LD_VX_I;
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

