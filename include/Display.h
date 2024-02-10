#pragma once

#include <array>
#include <cinttypes>
#include <cstddef>
#include <SDL2/SDL.h>


class Display {
public:
    static constexpr std::size_t kRawWidth {64};
    static constexpr std::size_t kRawHeight {32};
    // Typedef for ease of use handling the screen array
    typedef std::array<uint16_t, kRawWidth * kRawHeight> ScreenArrayT;

    ~Display();
    void Init();
    void Draw();
    void Clear();
    uint16_t& operator[] (std::size_t index);
    uint16_t& Coordinate (std::size_t x, std::size_t y);
    ScreenArrayT& Screen();

private:
    static constexpr std::size_t kDisplayScale {20};
    SDL_Window *window_ {nullptr};
    SDL_Renderer *renderer_ {nullptr};

    // Screen for the interpreter
    ScreenArrayT screen_;
};