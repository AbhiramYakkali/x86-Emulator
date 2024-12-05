#include <stdio.h>
#include <stdlib.h>

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

uint8_t get_next_byte(const uint8_t *memory, struct CPU *cpu) {
    return memory[cpu->eip++];
}

uint32_t read_next_word(const uint8_t *memory, struct CPU *cpu) {
    uint8_t bytes[4];

    for (int i = 0; i < 4; i++) {
        bytes[i] = get_next_byte(memory, cpu);
    }

    return bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

int main(const int argc, char **argv) {
    struct CPU cpu;
    uint8_t memory[MEMORY_SIZE];

    initialize_memory(memory);
    initialize_CPU(&cpu);

    auto filename = "test.bin";
    if (argc > 1) {
        filename = argv[1];
    }

    const auto program_length = load_program(filename, memory);
    if (program_length == 0) {
        printf("Failed to load %s\n", filename);
        return 1;
    }

    printf("Program length: %llu\n", program_length);
    cpu.ds = program_length;

    // Print binary code for debugging
    for (size_t i = 0; i < program_length; i++) {
        printf("%02x ", get_next_byte(memory, &cpu));
    }

    // Main emulator loop
    reset_CPU(&cpu);
    while (cpu.eip < program_length) {
        const auto opcode = get_next_byte(memory, &cpu);

        if (opcode == 0xF4) {
            // HLT, halt instruction
            printf("\nHalt instruction");
            //exit(1);
        }

        // MOV instructions
        if (opcode >= 0xB8 && opcode <= 0xBF) {
            // MOV, move immediate value to register
            const auto val = read_next_word(memory, &cpu);
            printf("\nMove instruction: ");
            printf("%02x", val);

            set_register(&cpu, opcode - 0xB8, val);
        }
        if (opcode == 0xA1) {
            // MOV, move byte at immediate memory location to EAX
            const auto address = read_next_word(memory, &cpu);
            cpu.eax = read_memory_relative(memory, address, &cpu);
        }
    }

    printf("\neax: %02x\necx: %02x", cpu.eax, cpu.ecx);

    return 0;
}
