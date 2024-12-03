//
// Created by ayakk on 12/3/2024.
//

#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"

#define MEMORY_SIZE 0x10000 //1 MB

void initialize_memory(uint8_t* memory);
uint8_t read_memory(const uint8_t* memory, uint32_t address);
void write_memory(uint8_t* memory, uint32_t address, uint8_t value);

#endif //MEMORY_H
