#include <iostream>

#include "../include/Display.h"

Display::~Display() {
    if (renderer_ != nullptr)
        SDL_DestroyRenderer(renderer_);
    if (window_ != nullptr)
        SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Display::Init() {
    window_ = SDL_CreateWindow("Sprocket's Chip8 Emulator", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, kRawWidth*kDisplayScale,
                              kRawHeight*kDisplayScale, 0);

    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return;
    }

    if (window_ == NULL) {
        std::cout << "Failed to create window\n";
        return;
    }

    if (renderer_ == NULL) {
        std::cout << "Failed to create renderer\n";
        return;
    }

    Clear();
}

void Display::Draw() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer_, 40, 40, 40, 255);  // Background color
    SDL_RenderClear(renderer_);

    // Draw the graphics
    SDL_SetRenderDrawColor(renderer_, 170, 230, 255, 255);  // Graphics color
    for (int x = 0; x < kRawWidth * kDisplayScale; x++) {
        for (int y = 0; y < kRawHeight * kDisplayScale; y++) {
        if (screen_[(x / kDisplayScale) + (y / kDisplayScale) * 64] == 1) {
            SDL_RenderDrawPoint(renderer_, x, y);
        }
        }
    }
    SDL_RenderPresent(renderer_); // Display the changes
}

void Display::Clear() {
    for (auto& pixel : screen_) {
        // Clear pixel
        pixel = 0;
    }
    Draw();
}

uint16_t& Display::operator[] (std::size_t index) {
    return screen_[index];
}

uint16_t& Display::Coordinate (std::size_t x, std::size_t y) {
    std::size_t index {y * kRawWidth + x};
    return screen_[index];
}

Display::ScreenArrayT& Display::Screen() {
    return screen_;
}