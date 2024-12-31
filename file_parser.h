//
// Created by ayakk on 12/20/2024.
//

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>

// Instructions are string arrays of length 4: mnemonic, optional operand, op1, op2,
// optional operand is usually used for size specifier
inline std::vector<std::vector<std::string>> instructions;

uint64_t parse_file(const std::string& file_name);
std::vector<std::string> get_instruction(uint32_t instruction);

#endif //FILE_PARSER_H
