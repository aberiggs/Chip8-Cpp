#include "../include/Chip8.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <thread>

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

Chip8::Chip8()
  : cpu_ {}
  , memory_ {}
  , display_ {}
  , keyboard_ {} {
    // Code to initialize the interpreter

    // Set program counter where rom will be loaded (0x200)
    cpu_.pc = 0x200;

    // Ensure that stack pointer is at base of the stack
    cpu_.sp = 0;

    // Load the fontset
    for (std::size_t i = 0; i < chip8_fontset.size(); ++i) {
        memory_[i] = chip8_fontset[i];
    }

    std::cout << "Chip8 successfully initialized.\n\n";
}

void Chip8::LoadRom(const std::string& rom_name) {
    FILE *rom {};
    rom = fopen(rom_name.c_str(), "rb");

    if (!rom) {
        throw std::runtime_error("File couldn't be opened or doesn't exist");
    }

    fread(&memory_[0x200], kRamSize - 0x200, 1, rom);

    std::cout << "Loaded: " << rom_name << ". Launching...\n\n";
}

void Chip8::Play() {
    auto time {std::chrono::system_clock::now().time_since_epoch()};
    auto time_ms {std::chrono::duration_cast<std::chrono::milliseconds>(time).count()};

    // Seed rand
    srand(time.count());

    // Initialize the display for rendering
    display_.Init();

    // Each run of the loop is 1 emulation cycle
    while (cpu_.pc < Memory::kRamSize - 1) {
        uint16_t currentOpcode = memory_[cpu_.pc] << 8 | memory_[cpu_.pc + 1];
        cpu_.pc += 2;

        Instruction currentInstruction {currentOpcode, cpu_, memory_, display_, keyboard_};
        currentInstruction.Execute();
    
        // De-increment timers as necessary
        if (cpu_.t_delay > 0) {
            auto new_time {std::chrono::system_clock::now().time_since_epoch()};
            auto new_time_ms {std::chrono::duration_cast<std::chrono::milliseconds>(new_time).count()};
            // De-increment @ 60hz
            if (new_time_ms - time_ms > 1000/60) {
                --cpu_.t_delay;
                time_ms = new_time_ms;
            }
        }

        if (cpu_.t_sound > 0) {
            std::cout << "BEEP\n";
            --cpu_.t_sound;
        }

        SDL_Event event {};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;
                case SDL_KEYDOWN:
                    keyboard_.CheckInput(event.key.keysym.scancode, true);
                    break;
                case SDL_KEYUP:
                    keyboard_.CheckInput(event.key.keysym.scancode, false);
                default:
                    break;
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(kDelayRate));
    }
}
