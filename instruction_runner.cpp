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

    printf("Unable to determine operand type for operand: %s\n", operand.c_str());
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

uint32_t instruction_runner::decode_memory_address(const std::string &memory_address, cpu* cpu) {
    // Determine the type of addressing (immediate or register relative)
    const auto address_type = determine_operand_type(memory_address, cpu);

    if (address_type == OPERAND_IMMEDIATE) {
        return decode_immediate(memory_address);
    }
    if (address_type == OPERAND_REGISTER) {
        return cpu->get_register(memory_address);
    }

    printf("Unrecognized memory address format: %s\n", memory_address.c_str());
    return 0;
}

uint32_t instruction_runner::get_value_from_operand(const std::string &operand, cpu *cpu) {
    switch (determine_operand_type(operand, cpu)) {
        case OPERAND_MEMORY: {
            // Isolate the value inside brackets and determine if it's a register or immediate
            const auto memory_address = operand.substr(1, operand.length() - 2);

            return cpu->get_memory_byte(decode_memory_address(memory_address, cpu));
        }
        case OPERAND_IMMEDIATE:
            return decode_immediate(operand);
        case OPERAND_REGISTER:
            return cpu->get_register(operand);
        default:
            printf("Unable to read value from operand: %s\n", operand.c_str());
            return 0;
    }
}

void instruction_runner::set_value_to_operand(const std::string &operand, const uint32_t value, cpu *cpu) {
    switch (determine_operand_type(operand, cpu)) {
        case OPERAND_MEMORY: {
            const auto memory_address = operand.substr(1, operand.length() - 2);
            cpu->set_memory_byte(decode_memory_address(memory_address, cpu), value);
            break;
        }
        case OPERAND_REGISTER:
            cpu->set_register(operand, value);
            break;
        default:
            printf("Unable to write value to operand: %s\n", operand.c_str());
            break;
    }
}


// Runs the specified instruction. Returns 0 if successful.
// Returns 1 if specified mnemonic does not exist
uint32_t instruction_runner::run_instruction(const std::vector<std::string>& instruction, cpu* cpu) const {
    instruction_function_map.at(instruction.at(0))(instruction, cpu);

    return 0;
}

void instruction_runner::initialize_instruction_function_map() {
    instruction_function_map["mov"] = run_instruction_move;
}

void instruction_runner::run_instruction_move(const std::vector<std::string>& instruction, cpu* cpu) {
    const auto value = get_value_from_operand(instruction[2], cpu);
    set_value_to_operand(instruction[1], value, cpu);
}
