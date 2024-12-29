//
// Created by ayakk on 12/20/2024.
//

#include "file_parser.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Returns the number of instructions in the file, 0 if error encountered
uint64_t parse_file(const std::string file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cout << "File " << file_name << " does not exist" << std::endl;
        return 0;
    }

    std::string line;
    // Read each line of the file, then split it into terms: mnemonic, op1, op2
    while (std::getline(file, line)) {
        std::vector<std::string> instruction;

        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            // Remove comma at the end of operand if it exists
            if (word.back() == ',') {
                word.pop_back();
            }

            transform(word.begin(), word.end(), word.begin(), tolower);
            instruction.push_back(word);
        }

        instruction.resize(4, "");
        instructions.push_back(instruction);
    }

    return instructions.size();
}

std::vector<std::string> get_instruction(const uint32_t instruction) {
    return instructions[instruction];
}
