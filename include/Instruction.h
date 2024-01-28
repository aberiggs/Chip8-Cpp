#pragma once

#include <array>
#include <iostream>

#include "Cpu.h"
#include "Memory.h"

class Instruction {
public:
    Instruction(short opcode, Cpu& c8_cpu, Memory& ch8_memory);
    void Execute();

private:
    // Ref to the CPU of the Ch8 instance for this instruction.
    Cpu& cpu_; 
    // Ref to the memory of the Ch8 instance for this instruction.
    Memory& memory_;
    // Original opcode
    short opcode_;
    // Pointer to the instruction to be executed.
    void (Instruction::*instruction_) (void) {UndefinedInstruction};

    
    void UndefinedInstruction();

};