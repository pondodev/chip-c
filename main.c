#include <stdio.h>

#include "main.h"
#include "instructions.h"

int main() {
    init();

    while (1) {
        cycle();
    }

    return 0;
}

void init() {
    core.pc = START_ADDRESS;

    // place fonts in memory
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        core.memory[FONT_SET_START_ADDRESS + i] = FONT_SET[i];
    }
}

void cycle() {
    uint16_t n1 = core.memory[core.pc] << 8;
    uint16_t n2 = core.memory[core.pc + 1];
    uint16_t opcode = n1 | n2;

    execute_instruction(opcode);

    core.pc += 2;
}
