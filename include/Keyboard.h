#pragma once

#include <array>
#include <cinttypes>
#include <SDL2/SDL.h>

class Keyboard {
public:
    uint8_t& operator[](uint8_t index);
    bool IsPressed(uint8_t key);
    void CheckInput(SDL_Scancode scancode, bool is_pressed);

private:
    std::array<uint8_t, 0x10> keyboard_;
};