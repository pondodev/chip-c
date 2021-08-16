#include <stdio.h>

#include "core.h"
#include "instructions.h"

const uint8_t FONT_SET[FONT_SET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

int init(char* rom_path, struct Core* core_ptr) {
    core_ptr->pc = START_ADDRESS;

    // place fonts in memory
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        core_ptr->memory[FONT_SET_START_ADDRESS + i] = FONT_SET[i];
    }

    // read in rom
    FILE* f = fopen(rom_path, "rb");

    if (!f) {
        return 4;
    }

    int c;
    int index = 0;
    while ((c = fgetc(f)) != EOF) {
        if (index >= MEMORY_SIZE) {
            return 4;
        }

        core_ptr->memory[index] = c;
        index++;
    }

    fclose(f);

    return 0;
}

int cycle(struct Core* core_ptr) {
    unsigned int n1_index = core_ptr->pc;
    unsigned int n2_index = core_ptr->pc + 1;

    if (n1_index >= MEMORY_SIZE || n2_index >= MEMORY_SIZE) {
        return 3;
    }

    uint16_t n1 = core_ptr->memory[n1_index] << 8;
    uint16_t n2 = core_ptr->memory[n2_index];
    uint16_t opcode = n1 | n2;

    execute_instruction(opcode, core_ptr);

    core_ptr->pc += 2;

    return 0;
}
