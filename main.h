#ifndef MAIN_H
#define MAIN_H

#include "core.h"
#include "instructions.h"

int error_code = 0;  // set to non-zero value when something goes wrong
/*
 * == error codes ==
 *
 * 3 - out of memory bounds
 * tried to access memory outside of chip8's memory space
 * 
 * 4 - rom load fail
 * rom either not found or failed to parse into memory
 * 
 * 5 - no rom path provided
 * rom path was not passed through as an argument
 */

struct Core core;

void init(char* rom_path);
void cycle();
uint16_t read_opcode();

#endif
