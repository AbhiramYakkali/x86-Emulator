//
// Created by ayakk on 12/21/2024.
//

#ifndef CPU_H
#define CPU_H
#include <cstdint>

#define REG_EAX 0
#define REG_EBX 1
#define REG_ECX 2
#define REG_EDX 3
#define REG_ESP 4
#define REG_EBP 5
#define REG_ESI 6
#define REG_EDI 7
#define REG_EIP 8
#define REG_EFLAGS 9

class cpu {
public:
    cpu();
    void reset();
    void set_register(int reg, uint32_t value);
    uint32_t get_register(int reg) const;

private:
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t eip, eflags;
};

#endif //CPU_H