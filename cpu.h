#pragma once
#include <stdint.h>

struct CPU {
    uint32_t eax, ebx, ecx, edx;
    uint32_t esp, ebp, esi, edi;
    uint32_t eip, eflags;
};

void initialize_CPU(struct CPU *cpu);
void reset_CPU(struct CPU *cpu);