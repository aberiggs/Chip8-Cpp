# Chip-8 Emulator
An introductory emulator for the simple interpreted language known as Chip-8.

![chip8pong](https://github.com/aberiggs/Chip8-Cpp/assets/34726295/761db127-1d78-4f43-9042-447fb8a2899e)


## Setup
I don't have any builds uploaded at the moment, but if you'd like to run this emulator the process of building from source should be fairly easy.

First, you'll want to install ```SDL2``` if you don't already have it. You can find the official guide for installation on the [SDL Wiki](https://wiki.libsdl.org/SDL2/Installation). If you're a Mac user you can also find ```SDL2``` on ```Homebrew```.


Next, make sure you have ```g++``` installed. If you'd rather use another compiler all you should have to do is modify the ```Makefile``` to pick the compiler of your choice. The ```Makefile``` might not work for you if you're on Windows as I haven't tested it yet. 

Now compile the project and you should be good to go! 

If you have any issues feel free to get in contact.

## Usage
After compiling from source, you should have some form of an executable.

From the project's root directory you can run either ```./Chip8``` (Linux/Mac users) or ```Chip8``` (Windows users)

After running the app, you will be prompted in the command line for a ROM to load. I have a couple in the ```roms``` folder, but you can also download more if you'd like. Make sure whatever you pick is the absolute path to that ROM from where you launched the app at.

E.g. If I wanted to run pong I'd input ```roms/Pong1.ch8```.

I will say that some games work better with a different delay rate, as the delay rate controls how many instructions are run per second. Later I may come back around and add arguments to set these kinds of things, but I'll leave it as it is for now. If you'd like to modify it yourself, you can find the constant, ```kDelayRate``` in ```include/Chip8.h```.
