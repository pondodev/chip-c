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
 */

struct Core core;

void init();
void cycle();
uint16_t read_opcode();

#endif
