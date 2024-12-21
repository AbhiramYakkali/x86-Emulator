#include <iostream>

#include "file_parser.h"

int main(const int argc, char *argv[]) {
    auto file_name = "file.asm";

    if (argc > 1) {
        file_name = argv[1];
    }

    parse_file(file_name);

    return 0;
}
