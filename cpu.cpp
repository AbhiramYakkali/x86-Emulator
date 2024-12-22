//
// Created by ayakk on 12/21/2024.
//

#include "cpu.h"

#include <cstdio>

cpu::cpu() {
    reset();
}

void cpu::reset() {
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
    esi = 0;
    edi = 0;
    ebp = 0;
    eip = 0;
    eflags = 0;
}

void cpu::set_register(const int reg, const uint32_t value) {
    switch (reg) {
        case REG_EAX:
            eax = value;
            break;
        case REG_EBX:
            ebx = value;
            break;
        case REG_ECX:
            ecx = value;
            break;
        case REG_EDX:
            edx = value;
            break;
        case REG_ESI:
            esi = value;
            break;
        case REG_EDI:
            edi = value;
            break;
        case REG_EBP:
            ebp = value;
            break;
        case REG_EIP:
            eip = value;
            break;
        case REG_EFLAGS:
            eflags = value;
            break;
        default:
            printf("Invalid register value in set_register: %d\n", reg);
            break;
    }
}

uint32_t cpu::get_register(const int reg) const {
    switch (reg) {
        case REG_EAX:
            return eax;
        case REG_EBX:
            return ebx;
        case REG_ECX:
            return ecx;
        case REG_EDX:
            return edx;
        case REG_ESI:
            return esi;
        case REG_EDI:
            return edi;
        case REG_EBP:
            return ebp;
        case REG_EIP:
            return eip;
        case REG_EFLAGS:
            return eflags;
        default:
            printf("Invalid register value in get_register: %d\n", reg);
            return 0;
    }
}