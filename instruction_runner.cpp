//
// Created by ayakk on 12/23/2024.
//

#include "instruction_runner.h"

#include <iostream>
#include <ostream>

instruction_runner::instruction_runner() {
    initialize_instruction_function_map();
}

uint32_t instruction_runner::determine_operand_type(const std::string &operand, cpu* cpu) {
    if (operand.empty()) return OPERAND_NONE;

    if (cpu->is_valid_register(operand)) return OPERAND_REGISTER;

    if (operand[0] == '[' && operand[operand.length() - 1] == ']') return OPERAND_MEMORY;

    auto is_integer = [](std::string str) {
        return std::all_of(str.begin(), str.end(), isdigit);
    };
    if (is_integer(operand)) return OPERAND_IMMEDIATE;

    printf("Unable to determine operand type for operand: %s", operand.c_str());
    return OPERAND_INVALID;
}

uint32_t instruction_runner::determine_operands_types(const std::vector<std::string>& instruction, cpu *cpu) {
    // Determine type of last operand (last digit)
    auto output = determine_operand_type(instruction[3], cpu);
    // Determine type of second operand (second digit)
    output += 10 * determine_operand_type(instruction[2], cpu);
    // Determine type of first operand (first digit)
    output += 100 * determine_operand_type(instruction[1], cpu);
    return output;
}

uint32_t instruction_runner::decode_immediate(const std::string &immediate) {
    // TODO: Decode other types of immediates
    return static_cast<uint32_t>(stoul(immediate));
}

uint32_t instruction_runner::get_value_from_operand(const std::string &operand, cpu *cpu) {
    switch (determine_operand_type(operand, cpu)) {
        case OPERAND_MEMORY: {
            // Isolate the value inside brackets and determine if it's a register or immediate
            const auto memory_address = operand.substr(1, operand.length() - 2);

            // Determine the type of addressing (immediate or register relative)
            const auto address_type = determine_operand_type(memory_address, cpu);

            if (address_type == OPERAND_IMMEDIATE) {
                return cpu->get_memory_byte(decode_immediate(memory_address));
            }
            if (address_type == OPERAND_REGISTER) {
                return cpu->get_memory_byte(cpu->get_register(memory_address));
            }
            printf("Unrecognized memory address: %s", memory_address.c_str());
            return 0;
        }
        case OPERAND_IMMEDIATE:
            return static_cast<uint32_t>(stoul(operand));
        case OPERAND_REGISTER:
            return cpu->get_register(operand);
        default:
            printf("Unable to determine operand type for operand: %s", operand.c_str());
            return 0;
    }
}


// Runs the specified instruction. Returns 0 if successful.
// Returns 1 if specified mnemonic does not exist
uint32_t instruction_runner::run_instruction(const std::vector<std::string>& instruction, cpu* cpu) const {
    instruction_function_map.at(instruction.at(0))(instruction, cpu);
    std::cout << determine_operands_types(instruction, cpu) << std::endl;

    return 0;
}

void instruction_runner::initialize_instruction_function_map() {
    instruction_function_map["mov"] = run_instruction_move;
}

void instruction_runner::run_instruction_move(const std::vector<std::string>& instruction, cpu* cpu) {
    cpu->set_register(instruction.at(1), static_cast<uint32_t>(stoul(instruction.at(2))));
}
