#pragma once

#include <array>
#include <cinttypes>
#include <cstddef>
#include <string_view>

#include "./Cpu.h"
#include "./Display.h"

class Chip8 {
public:
    // Initialize a Chip8 instance
    Chip8(std::string_view romName);

private:
    static constexpr std::size_t kRamSize {0x1000};
   
    // Cpu of the interpreter. Contains registers along with other information.
    Cpu cpu_ {};
    // The Chip8's memory. Programs start at 0x200.
    std::array<uint8_t, kRamSize> memory_ {};
    // The display for this instance of the Chip8 interpreter
    Display display_ {};

};