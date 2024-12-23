//
// Created by ayakk on 12/23/2024.
//

#include "instruction_runner.h"

instruction_runner::instruction_runner() {
    initialize_instruction_function_map();
}

uint32_t instruction_runner::run_instruction(const std::vector<std::string>& instruction, cpu* cpu) const {
    instruction_function_map.at(instruction.at(0))(instruction, cpu);

    return 0;
}

void instruction_runner::initialize_instruction_function_map() {
    instruction_function_map["mov"] = run_instruction_move;
}

void instruction_runner::run_instruction_move(const std::vector<std::string>& instruction, cpu* cpu) {
    cpu->set_register(instruction.at(1), static_cast<uint32_t>(stoul(instruction.at(2))));
}
