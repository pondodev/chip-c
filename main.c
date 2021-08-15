#include <stdio.h>

#include "main.h"

int main() {
    init();

    while (error_code == 0) {
        cycle();
    }

    switch (error_code) {
        case 3:
            printf("ERROR: out of memory bounds\n");
            break;

        default:
            printf("unrecognised exit code\n");
            break;
    }

    return error_code;
}

void init() {
    core.pc = START_ADDRESS;

    // place fonts in memory
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        core.memory[FONT_SET_START_ADDRESS + i] = FONT_SET[i];
    }
}

void cycle() {
    uint16_t opcode = read_opcode();

    execute_instruction(opcode);

    core.pc += 2;
}

uint16_t read_opcode() {
    unsigned int n1_index = core.pc;
    unsigned int n2_index = core.pc + 1;

    if (n1_index >= MEMORY_SIZE || n2_index >= MEMORY_SIZE) {
        error_code = 3;
    }

    uint16_t n1 = core.memory[n1_index] << 8;
    uint16_t n2 = core.memory[n2_index];

    return n1 | n2;
}
