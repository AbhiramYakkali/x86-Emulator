//
// Created by ayakk on 12/21/2024.
//

#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <map>
#include <string>

#define REG_EAX 1
#define REG_EBX 2
#define REG_ECX 3
#define REG_EDX 4
#define REG_ESP 5
#define REG_EBP 6
#define REG_ESI 7
#define REG_EDI 8
#define REG_EIP 9
#define REG_EFLAGS 10

// 4KB of memory by default
#define MEMORY_SIZE 4096

class cpu {
public:
    cpu();
    void reset();
    void set_register(uint32_t reg, uint32_t value);
    void set_register(std::string reg, uint32_t value);
    [[nodiscard]] uint32_t get_register(uint32_t reg) const;
    [[nodiscard]] uint32_t get_register(const std::string& reg);

    void set_memory_byte(uint32_t address, uint8_t value);
    [[nodiscard]] uint8_t get_memory_byte(uint32_t address) const;

    void increment_eip();

    [[nodiscard]] bool is_valid_register(const std::string& reg) const;

private:
    void initialize_register_map();

    std::map<std::string, uint32_t> registers;

    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t eip, eflags;

    uint8_t memory[MEMORY_SIZE];
};

#endif //CPU_H
