#pragma once

#include <array>
#include <cinttypes>
#include <cstddef>
#include <SDL2/SDL.h>


class Display {
public:
    Display();
    ~Display();
    // TODO: Probably want to do teardown at some point
    void Draw();
    

private:
    static constexpr std::size_t kRawWidth {64};
    static constexpr std::size_t kRawHeight {32};
    static constexpr std::size_t kDisplayScale {20};

    SDL_Window *window_ {nullptr};
    SDL_Renderer *renderer_ {nullptr};

    // Screen for the interpreter
    std::array<uint16_t, kRawWidth * kRawHeight> screen_;
};