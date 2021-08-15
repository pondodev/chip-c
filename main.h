#ifndef MAIN_H
#define MAIN_H 1

#include "core.h"

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

void handle_error_code();

#endif
