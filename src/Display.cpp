#include <iostream>

#include "../include/Display.h"

Display::Display() 
  : window_ {SDL_CreateWindow("Sprocket's Chip8 Emulator", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, kRawWidth*kDisplayScale,
                              kRawHeight*kDisplayScale, 0)}
  , renderer_ {SDL_CreateRenderer(window_, -1, 0)} {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return;
    }

    SDL_RenderClear(renderer_);  
}

Display::~Display() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Display::Draw() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer_, 40, 40, 40, 255);
    SDL_RenderClear(renderer_);

    // Draw the graphics
    SDL_SetRenderDrawColor(renderer_, 170, 230, 255, 255);
    for (int x = 0; x < kRawWidth * kDisplayScale; x++) {
        for (int y = 0; y < kRawHeight * kDisplayScale; y++) {
        if (screen_[(x / kDisplayScale) + (y / kDisplayScale) * 64] == 1) {
            SDL_RenderDrawPoint(renderer_, x, y);
        }
        }
    }
    SDL_RenderPresent(renderer_); // Display the changes
}