#pragma once

#include <array>
#include <cinttypes>

class Memory {
public:
    static constexpr std::size_t kRamSize {0x1000};

    uint8_t& operator[] (std::size_t index);
private:
    // The Chip8's memory. Programs start at 0x200.
    std::array<uint8_t, kRamSize> memory_ {};
};