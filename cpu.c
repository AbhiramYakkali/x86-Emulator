//
// Created by ayakk on 12/3/2024.
//

#include "cpu.h"

#include <string.h>

void initialize_CPU(struct CPU *cpu) {
    //Initialize all values (registers) in CPU to 0
    memset(cpu, 0, sizeof(struct CPU));
}

void reset_CPU(struct CPU *cpu) {
    //Reset all values in CPU to 0
    memset(cpu, 0, sizeof(struct CPU));
}
