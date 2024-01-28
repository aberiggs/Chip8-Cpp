#include "../include/Instruction.h"

Instruction::Instruction(short opcode, Cpu& c8_cpu, Memory& ch8_memory)
  : opcode_ {opcode}
  , cpu_ {c8_cpu}
  , memory_ {ch8_memory} {
    // Get instruction to call from opcode
    
    
}

void Instruction::UndefinedInstruction() {
    //TODO: Maybe throw exception to be caught further up?
    std::cout << "Instruction undefined...\n";
}

