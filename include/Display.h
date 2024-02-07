#pragma once

#include <array>
#include <cinttypes>
#include <cstddef>
#include <SDL2/SDL.h>


class Display {
private: 
    // Constexpr variables for typedef
    static constexpr std::size_t kRawWidth {64};
    static constexpr std::size_t kRawHeight {32};
    static constexpr std::size_t kDisplayScale {20};

public:
    // Typedef for ease of use handling the screen array
    typedef std::array<uint16_t, kRawWidth * kRawHeight> ScreenArrayT;

    Display();
    ~Display();
    void Draw();
    uint16_t& operator[] (std::size_t index);
    ScreenArrayT& Screen();

private:
    SDL_Window *window_ {nullptr};
    SDL_Renderer *renderer_ {nullptr};

    // Screen for the interpreter
    ScreenArrayT screen_;
};