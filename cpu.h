#pragma once
#include <stdint.h>

struct CPU {
    uint32_t eax, ebx, ecx, edx;
    uint32_t esp, ebp, esi, edi;
    uint32_t eip, eflags;

    uint16_t cs, ds, ss, es, fs, gs;
};

void initialize_CPU(struct CPU *cpu);
void reset_CPU(struct CPU *cpu);

void set_register(struct CPU *cpu, uint32_t reg, uint32_t value);
uint32_t get_register(const struct CPU *cpu, uint32_t reg);