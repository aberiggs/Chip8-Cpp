#include "../include/Chip8.h"


#include <fstream>
#include <iostream>
#include <iterator>
#include <thread>

#include <chrono>
#include "../include/Instruction.h"

constexpr std::array<uint16_t, 80> chip8_fontset = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8(const std::string& rom_name)
  : cpu_ {}
  , memory_ {}
  , display_ {} {
    // Code to initialize the interpreter

    // Set program counter where rom will be loaded (0x200)
    cpu_.pc = 0x200;

    // Ensure that stack pointer is at base of the stack
    cpu_.sp = 0;

    // Load the fontset
    for (std::size_t i = 0; i < chip8_fontset.size(); ++i) {
        memory_[i] = chip8_fontset[i];
    }

    /*


    // Read rom data into a buffer
    std::ifstream rom_stream(rom_name, std::ios::binary);
    if (!rom_stream) {
        // TODO: Some exception
        std::cout << "Failed to open file!\n";
        return;
    }
    char* rom_buff = new char[kRamSize - 0x200];
    rom_stream.readsome(rom_buff, kRamSize - 0x200);
    
    if (!rom_stream) {
        // TODO: Some other exception
        std::cout << "Failed to read stream into buffer!\n";
        return;
    }

    // Copy rom data into memory
    for (std::size_t i = 0x200; i < kRamSize; ++i ) {
        memory_[i] = rom_buff[i - 0x200];
    }

    delete[] rom_buff;
    */

    FILE *rom = 0;
    rom = fopen(rom_name.c_str(), "rb");

    if (!rom) {
        std::cout << "Failed to open file!\n";
        return;
    }

    fread(&memory_[0x200], kRamSize - 0x200, 1, rom);


    std::cout << "Chip8 successfully initialized. Launching: " << rom_name << "\n";
}

void Chip8::Play() {
    // Each run of the loop is 1 emulation cycle
    while (cpu_.pc < Memory::kRamSize) {
        uint16_t currentOpcode = memory_[cpu_.pc] << 8 | memory_[cpu_.pc + 1];
        printf("\nOpcode: 0x%x, pc: %d\n", currentOpcode, cpu_.pc);
        cpu_.pc += 2;
        
        //std::cout << "Opcode: " << currentOpcode << "\n";

        Instruction currentInstruction {currentOpcode, cpu_, memory_, display_};
        currentInstruction.Execute();
    
        // De-increment timers as necessary
        if (cpu_.t_delay > 0) {
            --cpu_.t_delay;
        }
        if (cpu_.t_sound > 0) {
            std::cout << "BEEP";
            --cpu_.t_sound;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(kDelayRate));
    }

    std::cout << "pc @ " << cpu_.pc << "\n";
}
