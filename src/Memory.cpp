#include "../include/Memory.h"

uint8_t& Memory::operator[] (std::size_t index) {
    return memory_[index];
}