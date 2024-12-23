//
// Created by ayakk on 12/23/2024.
//

#ifndef INSTRUCTION_RUNNER_H
#define INSTRUCTION_RUNNER_H

#include <functional>

#include "cpu.h"

class instruction_runner {
public:
    instruction_runner();

    uint32_t run_instruction(const std::vector<std::string>& instruction, cpu* cpu) const;

private:
    std::map<std::string, std::function<void(const std::vector<std::string>&, cpu*)>> instruction_function_map;

    void initialize_instruction_function_map();

    // Instruction functions
    static void run_instruction_move(const std::vector<std::string>& instruction, cpu* cpu);
};

#endif //INSTRUCTION_RUNNER_H
