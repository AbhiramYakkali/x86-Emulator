//
// Created by ayakk on 12/3/2024.
//

#include "memory.h"

#include <stdio.h>
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

uint8_t read_memory_relative(const uint8_t* memory, const uint32_t address, const struct CPU *cpu) {
    const uint32_t real_address = address + cpu->ds;

    if (real_address > MEMORY_SIZE) {
        printf("Error reading address %02x: address is outside of available memory\n", real_address);
    }

    return read_memory(memory, real_address);
}

void write_memory_relative(uint8_t* memory, const uint32_t address, const uint8_t value, const struct CPU *cpu) {
    const uint32_t real_address = address + cpu->ds;

    if (real_address > MEMORY_SIZE) {
        printf("Error writing to address %02x: address is outside of available memory\n", real_address);
    }

    write_memory(memory, real_address, value);
}

