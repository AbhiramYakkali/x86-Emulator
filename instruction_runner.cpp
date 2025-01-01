//
// Created by ayakk on 12/23/2024.
//

#include "instruction_runner.h"

#include <iostream>
#include <variant>

instruction_runner::instruction_runner() {
    initialize_instruction_function_map();
}

uint32_t instruction_runner::determine_operand_type(const std::string &operand, const cpu* cpu) {
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

uint32_t instruction_runner::determine_operands_types(const std::vector<std::string>& instruction, const cpu *cpu) {
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

value_size instruction_runner::get_value_from_operand(const std::string &operand, const std::string &size, uint32_t operand_type, cpu *cpu) {
    switch (operand_type) {
        case OPERAND_MEMORY: {
            // Isolate the value inside brackets and determine if it's a register or immediate
            const auto memory_address_string = operand.substr(1, operand.length() - 2);
            const auto memory_address = decode_memory_address(memory_address_string, cpu);

            if (size == "byte") return cpu->get_memory_byte(memory_address);
            if (size == "word") return cpu->get_memory_word(memory_address);
            if (size == "dword") return cpu->get_memory_dword(memory_address);
            if (size == "qword") return cpu->get_memory_qword(memory_address);

            if (size.empty()) printf("Missing size specifier associated with operand %s\n", operand.c_str());
            else printf("Invalid size specifier %s for operand %s\n", size.c_str(), operand.c_str());

            return static_cast<uint8_t>(0);
        }
        case OPERAND_IMMEDIATE: {
            const auto value = decode_immediate(operand);

            if (size == "byte") return static_cast<uint8_t>(value);
            if (size == "word") return static_cast<uint16_t>(value);
            if (size == "qword") return static_cast<uint64_t>(value);
            return value; // Default size is 32 bits (dword)
        }
        case OPERAND_REGISTER:
            return cpu->get_register(operand);
        default:
            printf("Unable to read value from operand: %s\n", operand.c_str());
        return static_cast<uint8_t>(0);
    }
}

value_size instruction_runner::get_value_from_operand(const std::string &operand, const std::string& size, cpu *cpu) {
    return get_value_from_operand(operand, size, determine_operand_type(operand, cpu), cpu);
}

void instruction_runner::set_value_to_operand(const std::string &operand, value_size value, const std::string &size, uint32_t operand_type, cpu *cpu) {
    switch (operand_type) {
        case OPERAND_MEMORY: {
            const auto memory_address_string = operand.substr(1, operand.length() - 2);
            const auto memory_address = decode_memory_address(memory_address_string, cpu);

            if (size == "byte") cpu->set_memory_byte(memory_address, std::get<uint8_t>(value));
            if (size == "word") cpu->set_memory_word(memory_address, std::get<uint16_t>(value));
            if (size == "dword") cpu->set_memory_dword(memory_address, std::get<uint32_t>(value));
            if (size == "qword") cpu->set_memory_qword(memory_address, std::get<uint64_t>(value));

            break;
        }
        case OPERAND_REGISTER:
            cpu->set_register(operand, std::get<uint32_t>(value));
        break;
        default:
            printf("Unable to write value to operand: %s\n", operand.c_str());
        break;
    }
}

void instruction_runner::set_value_to_operand(const std::string &operand, const value_size value, const std::string& size, cpu *cpu) {
    set_value_to_operand(operand, value, size, determine_operand_type(operand, cpu), cpu);
}


// Runs the specified instruction. Returns 0 if successful.
// Returns 1 if specified mnemonic does not exist
uint32_t instruction_runner::run_instruction(const std::vector<std::string>& instruction, cpu* cpu) const {
    instruction_function_map.at(instruction.at(0))(instruction, cpu);

    return 0;
}

void instruction_runner::initialize_instruction_function_map() {
    instruction_function_map["mov"] = run_instruction_move;
    instruction_function_map["xchg"] = run_instruction_xchg;
}

void instruction_runner::run_instruction_move(const std::vector<std::string>& instruction, cpu* cpu) {
    const auto& size_specifier = instruction[4];
    const auto value = get_value_from_operand(instruction[2], size_specifier, cpu);
    set_value_to_operand(instruction[1], value, size_specifier, cpu);
}

void instruction_runner::run_instruction_xchg(const std::vector<std::string> &instruction, cpu *cpu) {
    const auto& size_specifier = instruction[4];

    const auto val1 = get_value_from_operand(instruction[1], size_specifier, cpu);
    const auto val2 = get_value_from_operand(instruction[2], size_specifier, cpu);

    set_value_to_operand(instruction[2], val1, size_specifier, cpu);
    set_value_to_operand(instruction[1], val2, size_specifier, cpu);
}

