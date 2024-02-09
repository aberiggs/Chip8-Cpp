#include "../include/Keyboard.h"


uint8_t& Keyboard::operator[](uint8_t index) {
    return keyboard_[index];
}

bool Keyboard::IsPressed(uint8_t key) {
    return keyboard_[key] == 1;
}

void Keyboard::CheckInput(SDL_Scancode scancode, bool is_pressed) {
    uint8_t press_status {static_cast<uint8_t>(is_pressed)};

    switch (scancode) {
        case SDL_SCANCODE_1:
            keyboard_[0x0] = press_status;
            break;
        case SDL_SCANCODE_2:
            keyboard_[0x1] = press_status;
            break;
        case SDL_SCANCODE_3:
            keyboard_[0x2] = press_status;
            break;
        case SDL_SCANCODE_4:
            keyboard_[0xC] = press_status;
            break;
        case SDL_SCANCODE_Q:
            keyboard_[0x4] = press_status;
            break;
        case SDL_SCANCODE_W:
            keyboard_[0x5] = press_status;
            break;
        case SDL_SCANCODE_E:
            keyboard_[0x6] = press_status;
            break;
        case SDL_SCANCODE_R:
            keyboard_[0x7] = press_status;
            break;
        case SDL_SCANCODE_A:
            keyboard_[0x8] = press_status;
            break;
        case SDL_SCANCODE_S:
            keyboard_[0x9] = press_status;
            break;
        case SDL_SCANCODE_D:
            keyboard_[0xA] = press_status;
            break;
        case SDL_SCANCODE_F:
            keyboard_[0xB] = press_status;
            break;
        case SDL_SCANCODE_Z:
            keyboard_[0xC] = press_status;
            break;
        case SDL_SCANCODE_X:
            keyboard_[0xD] = press_status;
            break;
        case SDL_SCANCODE_C:
            keyboard_[0xE] = press_status;
            break;
        case SDL_SCANCODE_V:
            keyboard_[0xF] = press_status;
            break;
        default:
            break;
    }
}
