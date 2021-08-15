#ifndef CORE_H
#define CORE_H 1

#include <stdint.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define VIDEO_SIZE SCREEN_WIDTH * SCREEN_HEIGHT + 1
#define START_ADDRESS 0x200
#define MEMORY_SIZE 4096

struct Core {
    uint8_t registers[16];
    uint8_t memory[MEMORY_SIZE];
    uint16_t stack[16];
    uint16_t index;
    uint16_t pc;
    uint16_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
    uint32_t video[VIDEO_SIZE];
};

#define FONT_SET_SIZE 80
#define FONT_SET_START_ADDRESS 0x50
extern const uint8_t FONT_SET[FONT_SET_SIZE];

int init(char* rom_path, struct Core* core);
int cycle(struct Core* core);

#endif
