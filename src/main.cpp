#include <iostream>
#include <stdexcept>
#include <string>

#include "../include/Chip8.h"

int main() {
    std::cout << "Welcome to Sprocket's Chip8 Emulator!\n";

    Chip8 ch8 {};

    while (true) {
        try {
            std::cout << "Rom to load (path): ";
            std::string rom_name {};
            std::cin >> rom_name;
            // If we made it here it must have loaded
            ch8.LoadRom(rom_name);
            break;
        } catch (const std::exception& e) {
            std::cerr << "\nException: " << e.what() << "\n\n";
        }
    }
   
    ch8.Play();
    
    return 0;
}