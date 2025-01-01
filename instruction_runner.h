//
// Created by ayakk on 12/23/2024.
//

#ifndef INSTRUCTION_RUNNER_H
#define INSTRUCTION_RUNNER_H

#include <functional>
#include <variant>

#include "cpu.h"

#define OPERAND_NONE 0
#define OPERAND_IMMEDIATE 1
#define OPERAND_REGISTER 2
#define OPERAND_MEMORY 3
#define OPERAND_INVALID 4

using value_size = std::variant<uint8_t, uint16_t, uint32_t, uint64_t>;

class instruction_runner {
public:
    instruction_runner();

    uint32_t run_instruction(const std::vector<std::string>& instruction, cpu* cpu) const;

private:
    std::map<std::string, std::function<void(const std::vector<std::string>&, cpu*)>> instruction_function_map;

    void initialize_instruction_function_map();

    // Helper functions for running instructions
    // Returns OPERAND_ + NONE, IMMEDIATE, REGISTER, MEMORY, or INVALID
    [[nodiscard]] static uint32_t determine_operand_type(const std::string &operand, const cpu* cpu);
    // Returns a three digit number (ex: 210 for register, immediate, none) representing all operand types
    static uint32_t determine_operands_types(const std::vector<std::string>& instruction, const cpu* cpu);

    // Converts an immediate string (100, 0x100, etc.) into a uint32
    static uint32_t decode_immediate(const std::string& immediate);
    // Returns the address associated with a memory address based on addressing type (immediate, register, etc.)
    static uint32_t decode_memory_address(const std::string& memory_address, cpu* cpu);

    // Takes in operand and returns the value from register, immediate, or memory
    static value_size get_value_from_operand(const std::string &operand, const std::string& size, cpu* cpu);
    // Allow this function to be called with operand type known beforehand
    // Allows instruction functions to check operand types without running d_o_t multiple times
    static value_size get_value_from_operand(const std::string &operand, const std::string& size, uint32_t operand_type, cpu* cpu);
    // Takes in operand sets a value to register or memory
    static void set_value_to_operand(const std::string &operand, value_size value, const std::string& size, cpu* cpu);
    static void set_value_to_operand(const std::string &operand, value_size value, const std::string& size, uint32_t operand_type, cpu* cpu);

    // Functions for specific instructions
    static void run_instruction_move(const std::vector<std::string>& instruction, cpu* cpu);
    static void run_instruction_xchg(const std::vector<std::string>& instruction, cpu* cpu);
};

#endif //INSTRUCTION_RUNNER_H
