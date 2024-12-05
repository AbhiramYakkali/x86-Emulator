//
// Created by ayakk on 12/3/2024.
//

#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"

#include "cpu.h"

#define MEMORY_SIZE 0x10000 //1 MB

void initialize_memory(uint8_t* memory);
uint8_t read_memory(const uint8_t* memory, uint32_t address);
void write_memory(uint8_t* memory, uint32_t address, uint8_t value);

// Reads/writes memory relative to the end of the program (ie. address 0 = first byte after end of program in memory)
uint8_t read_memory_relative(const uint8_t* memory, uint32_t address, const struct CPU *cpu);
void write_memory_relative(uint8_t* memory, uint32_t address, uint8_t value, const struct CPU *cpu);

#endif //MEMORY_H
