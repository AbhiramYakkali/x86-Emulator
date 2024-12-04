#include <stdio.h>

#include "cpu.h"
#include "memory.h"

int main(void) {
    struct CPU cpu;
    uint8_t memory[MEMORY_SIZE];

    initialize_memory(memory);
    initialize_CPU(&cpu);

    return 0;
}
