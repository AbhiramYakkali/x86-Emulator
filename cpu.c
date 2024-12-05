//
// Created by ayakk on 12/3/2024.
//

#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_CPU(struct CPU *cpu) {
    //Initialize all values (registers) in CPU to 0
    memset(cpu, 0, sizeof(struct CPU));
}

void reset_CPU(struct CPU *cpu) {
    //Reset all values in CPU to 0
    memset(cpu, 0, sizeof(struct CPU));
}

//Used when accessing registers by index (simplifies handling of instructions that refer to registers)
void set_register(struct CPU *cpu, const uint32_t reg, const uint32_t value) {
    switch (reg) {
        case 0:
            cpu->eax = value;
            break;
        case 1:
            cpu->ecx = value;
            break;
        case 2:
            cpu->edx = value;
            break;
        case 3:
            cpu->ebx = value;
            break;
        case 4:
            cpu->esp = value;
            break;
        case 5:
            cpu->ebp = value;
            break;
        case 6:
            cpu->esi = value;
            break;
        case 7:
            cpu->edi = value;
            break;
        default:
            printf("Invalid register value: %d\n", reg);
            exit(1);
    }
}
uint32_t get_register(const struct CPU *cpu, const uint32_t reg) {
    switch (reg) {
        case 0:
            return cpu->eax;
        case 1:
            return cpu->ecx;
        case 2:
            return cpu->edx;
        case 3:
            return cpu->ebx;
        case 4:
            return cpu->esp;
        case 5:
            return cpu->ebp;
        case 6:
            return cpu->esi;
        case 7:
            return cpu->edi;
        default:
            printf("Invalid register value: %d\n", reg);
            exit(1);
    }
}
