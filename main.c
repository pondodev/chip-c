#include <stdio.h>

#include "main.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        error_code = 5;
    } else {
        init(argv[1]);
    }

    while (error_code == 0) {
        printf("%04x: ", core.pc);
        cycle();
    }

    switch (error_code) {
        case 3:
            printf("ERROR: out of memory bounds\n");
            break;

        case 4:
            printf("ERROR: failed to read rom\n");
            break;

        default:
            printf("unrecognised exit code\n");
            break;
    }

    return error_code;
}

void init(char* rom_path) {
    core.pc = START_ADDRESS;

    // place fonts in memory
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        core.memory[FONT_SET_START_ADDRESS + i] = FONT_SET[i];
    }

    // read in rom
    FILE* f = fopen(rom_path, "rb");

    if (!f) {
        error_code = 4;
        return;
    }

    int c;
    int index = 0;
    while ((c = fgetc(f)) != EOF) {
        if (index >= MEMORY_SIZE) {
            error_code = 4;
            return;
        }

        core.memory[index] = c;
        index++;
    }

    fclose(f);
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
