#pragma once

#include <cinttypes>
#include <array>

struct Cpu {
    // Program counter.
    uint16_t pc {};
    // Stack pointer.
    uint8_t sp {};
    // Array of 8-bit registers that are referred to as 'Vx'.
    std::array<uint8_t, 0x10> V {};
    // Stack to contain addresses to return to following subroutines.
    std::array<uint16_t, 0x10> stack {};
    // 16-bit register (usually) used to store memory addresses.
    uint16_t I {};
    // 8-bit register for the delay timer.
    uint8_t t_delay {};
    // 8-bit register for the sound timer.
    uint8_t t_sound {};
};