#include <iostream>

#define NORMAL_EXIT 0
#define PARSING_ERROR (-1)

#include "cpu.h"
#include "file_parser.h"

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

    while (cpu.get_register(REG_EIP) < instruction_count) {
        const auto instruction = get_instruction(cpu.get_register(REG_EIP));
    }

    return 0;
}
