#pragma once

#include <array>
#include <cinttypes>
#include <cstddef>


class Display {
public:

private:
    static constexpr std::size_t kRawWidth {64};
    static constexpr std::size_t kRawHeight {32};
    static constexpr std::size_t kDisplayScale {20};

    // Screen for the interpreter
    std::array<uint16_t, kRawWidth * kRawHeight> screen_;
};