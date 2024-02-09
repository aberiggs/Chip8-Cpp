#pragma once

#include <array>
#include <cinttypes>
#include <cstddef>
#include <string_view>

#include "Cpu.h"
#include "Display.h"
#include "Keyboard.h"
#include "Memory.h"

class Chip8 {
public:
    // Initialize a Chip8 instance
    Chip8(const std::string& rom_name);
    void Play();

private:
    static constexpr std::size_t kRamSize {0x1000};
    // Delay rate for each emulation cycle in ms. 1000/60 ~ 60 fps
    static constexpr int kDelayRate {static_cast<int>(1000/60)};
   
    // Cpu of the interpreter. Contains registers along with other information.
    Cpu cpu_ {};
    // The Chip8's memory. Programs start at 0x200.
    Memory memory_ {};
    // The display for this instance of the Chip8 interpreter
    Display display_ {};
    // The keyboard for this instance of the Chip8 interpreter
    Keyboard keyboard_ {};
};