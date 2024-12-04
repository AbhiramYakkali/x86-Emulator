#include <stdio.h>

#include "cpu.h"
#include "memory.h"

uint64_t load_program(const char *filename, uint8_t *memory) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return 0;
    }

    const uint64_t length = fread(memory, 1, MEMORY_SIZE, file);
    return length;
}

int main(const int argc, char **argv) {
    struct CPU cpu;
    uint8_t memory[MEMORY_SIZE];

    initialize_memory(memory);
    initialize_CPU(&cpu);

    auto filename = "test.o";
    if (argc > 1) {
        filename = argv[1];
    }

    const auto program_length = load_program(filename, memory);
    if (program_length == 0) {
        printf("Failed to load %s\n", filename);
        return 1;
    }

    printf("Program length: %llu\n", program_length);

    return 0;
}
