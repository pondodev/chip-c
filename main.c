#include <stdio.h>

#include "main.h"

int main() {
    init();

    return 0;
}

void init() {
    core.pc = START_ADDRESS;

    // place fonts in memory
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        core.memory[FONT_SET_START_ADDRESS + i] = FONT_SET[i];
    }
}
