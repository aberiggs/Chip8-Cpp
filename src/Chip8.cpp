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

    // Set program counter where rom will be loaded
    cpu_.pc = 0x200;

    // Load the fontset
    for (std::size_t i = 0; i < chip8_fontset.size(); ++i) {
        memory_[i] = chip8_fontset[i];
    }

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

    std::cout << "Chip8 successfully initialized. Launching: " << rom_name << "\n";
}

void Chip8::Play() {
    // Each run of the loop is 1 emulation cycle
    while (true) {
        unsigned short currentOpcode = memory_[cpu_.pc] << 8 | memory_[cpu_.pc + 1];

        Instruction currentInstruction {currentOpcode, cpu_, memory_, display_};
        // currentInstruction.Execute();

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
}
