#pragma once

#include <array>
#include <iostream>

#include "Cpu.h"
#include "Display.h"
#include "Memory.h"

class Instruction {
public:
    Instruction(unsigned short opcode, Cpu& c8_cpu, Memory& ch8_memory, Display& ch8_display);
    void Execute();

private:
    // Ref to the CPU of the Ch8 instance for this instruction.
    Cpu& cpu_; 
    // Ref to the memory of the Ch8 instance for this instruction.
    Memory& memory_;
    // Ref to the display of the Ch8 instance for this instruction.
    Display& display_;
    // Original opcode
    unsigned short opcode_;

    typedef void (Instruction::*InstructionMemFn) (void);
    // Pointer to the instruction to be executed.
    InstructionMemFn instruction_ {Instruction::UndefinedInstruction};


    inline unsigned short ADDR_() {
        return (opcode_);
    }

    inline unsigned short N_() {
        return (opcode_ & 0xFFF);
    }
        
    inline unsigned short X_() {
        return (opcode_ & 0xF00) >> 8;
    }
    inline unsigned short Y_() {
        return (opcode_ & 0xF0) >> 4;
    }
    inline unsigned short KK_() {
        return (opcode_ & 0xFF);
    }
    

    
    void UndefinedInstruction();

    void CLS();
    void RET();
    void JP_ADDR();
    void CALL_ADDR();
    void SE_VX_KK();
    void SNE_VX_KK();
    void SE_VX_VY();
    void LD_VX_KK();
    void ADD_VX_KK();
    void LD_VX_VY();
    void OR_VX_VY();
    void AND_VX_VY();
    void XOR_VX_VY();
    void ADD_VX_VY();
    void SUB_VX_VY();
    void SHR_VX();
    void SUBN_VX_VY();
    void SHL_VX();
    void SNE_VX_VY();
    void LD_I_ADDR();
    void JP_V0_ADDR();
    void RND_VX_KK();
    void DRW_VX_VY_N();
    void SKP_VX();
    void SKNP_VX();
    void LD_VX_DT();
    void LD_VX_K();
    void LD_DT_VX();
    void LD_ST_VX();
    void ADD_I_VX();
    void LD_F_VX();
    void LD_B_VX();
    void LD_I_VX();
    void LD_VX_I();
};