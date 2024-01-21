#include <iostream>
#include <string>

#include "../include/Chip8.h"

int main() {
    std::cout << "Welcome to Sprocket's Chip8 Emulator!\n";
    std::cout << "Rom to load: ";
    std::string rom_name {};
    std::cin >> rom_name;

    Chip8 ch8 {rom_name};
    
}