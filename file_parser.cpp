//
// Created by ayakk on 12/20/2024.
//

#include "file_parser.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Returns whether parsing was successful or not
bool parse_file(const std::string file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cout << "File " << file_name << " does not exist" << std::endl;
        return false;
    }

    std::string line;
    // Read each line of the file, then split it into terms: mnemonic, op1, op2
    while (std::getline(file, line)) {
        std::vector<std::string> instruction;

        std::cout << line << std::endl;

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

        instructions.push_back(instruction);
    }

    return true;
}
