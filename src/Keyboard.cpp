#include "../include/Keyboard.h"


uint8_t& Keyboard::operator[](uint8_t index) {
    return keyboard_[index];
}

bool Keyboard::IsPressed(uint8_t key) {
    return keyboard_[key] == 1;
}

uint8_t *Keyboard::CheckInput(SDL_Scancode scancode, bool is_pressed) {
    uint8_t *key_ptr {nullptr};

    switch (scancode) {
        case SDL_SCANCODE_1:
            key_ptr = &keyboard_[0x1];
            break;
        case SDL_SCANCODE_2:
            key_ptr = &keyboard_[0x2];
            break;
        case SDL_SCANCODE_3:
            key_ptr = &keyboard_[0x3];
            break;
        case SDL_SCANCODE_4:
            key_ptr = &keyboard_[0xC];
            break;
        case SDL_SCANCODE_Q:
            key_ptr = &keyboard_[0x4];
            break;
        case SDL_SCANCODE_W:
            key_ptr = &keyboard_[0x5];
            break;
        case SDL_SCANCODE_E:
            key_ptr = &keyboard_[0x6];
            break;
        case SDL_SCANCODE_R:
            key_ptr = &keyboard_[0xD];
            break;
        case SDL_SCANCODE_A:
            key_ptr = &keyboard_[0x7];
            break;
        case SDL_SCANCODE_S:
            key_ptr = &keyboard_[0x8];
            break;
        case SDL_SCANCODE_D:
            key_ptr = &keyboard_[0x9];
            break;
        case SDL_SCANCODE_F:
            key_ptr = &keyboard_[0xE];
            break;
        case SDL_SCANCODE_Z:
            key_ptr = &keyboard_[0xA];
            break;
        case SDL_SCANCODE_X:
            key_ptr = &keyboard_[0x0];
            break;
        case SDL_SCANCODE_C:
            key_ptr = &keyboard_[0xB];
            break;
        case SDL_SCANCODE_V:
            key_ptr = &keyboard_[0xF];
            break;
        default:
            break;
    }

    if (key_ptr != nullptr)
        *key_ptr = static_cast<uint8_t>(is_pressed);

    return key_ptr;
}
