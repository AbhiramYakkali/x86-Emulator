//
// Created by ayakk on 12/3/2024.
//

#include "memory.h"

#include <string.h>

void initialize_memory(uint8_t* memory) {
    memset(memory, 0, MEMORY_SIZE);
}

uint8_t read_memory(const uint8_t* memory, const uint32_t address) {
    return memory[address];
}

void write_memory(uint8_t* memory, const uint32_t address, const uint8_t value) {
    memory[address] = value;
}
