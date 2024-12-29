#include <iostream>

#define NORMAL_EXIT 0
#define PARSING_ERROR (-1)

#include <functional>
#include <map>

#include "cpu.h"
#include "file_parser.h"
#include "instruction_runner.h"

int main(const int argc, char *argv[]) {
    auto file_name = "file.asm";

    if (argc > 1) {
        file_name = argv[1];
    }

    const auto instruction_count = parse_file(file_name);

    if (instruction_count == 0) {
        std::cerr << "Error parsing file: " << file_name << std::endl;
        return PARSING_ERROR;
    }

    cpu cpu;
    const instruction_runner runner;

    while (cpu.get_register(REG_EIP) < instruction_count) {
        const auto instruction = get_instruction(cpu.get_register(REG_EIP));

        // Handle halt here, not worth making a new function for it
        if (instruction.at(0) == "hlt") {
            exit(0);
        }

        runner.run_instruction(instruction, &cpu);

        cpu.increment_eip();
    }

    return 0;
}
