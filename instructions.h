#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H 1

#include <stdint.h>
#include <stdlib.h>

#include "core.h"

void execute_instruction(uint16_t opcode, struct Core* core_ptr);

// opcode transforms
void get_nibbles(uint16_t opcode, uint8_t* out);
uint16_t get_address(uint16_t opcode);
void process_op_5xxx(uint16_t opcode, struct Core* core_ptr);
void process_op_8xxx(uint16_t opcode, struct Core* core_ptr);
void process_op_9xxx(uint16_t opcode, struct Core* core_ptr);
void process_op_9xxx(uint16_t opcode, struct Core* core_ptr);
void process_op_exxx(uint16_t opcode, struct Core* core_ptr);
void process_op_fxxx(uint16_t opcode, struct Core* core_ptr);

// instruction definitions, based off cowgod's chip8 reference
void op_00e0(struct Core* core_ptr);                  // cls
void op_00ee(struct Core* core_ptr);                  // ret
void op_0nnn(uint16_t opcode, struct Core* core_ptr); // sys  <addr>
void op_1nnn(uint16_t opcode, struct Core* core_ptr); // jp   <addr>
void op_2nnn(uint16_t opcode, struct Core* core_ptr); // call <addr>
void op_3xkk(uint16_t opcode, struct Core* core_ptr); // se   <Vx>, <byte>
void op_4xkk(uint16_t opcode, struct Core* core_ptr); // sne  <Vx>, <byte>
void op_5xy0(uint16_t opcode, struct Core* core_ptr); // se   <Vx>, <Vy>
void op_6xkk(uint16_t opcode, struct Core* core_ptr); // ld   <Vx>, <byte>
void op_7xkk(uint16_t opcode, struct Core* core_ptr); // add  <Vx>, <byte>
void op_8xy0(uint16_t opcode, struct Core* core_ptr); // ld   <Vx>, <Vy>
void op_8xy1(uint16_t opcode, struct Core* core_ptr); // or   <Vx>, <Vy>
void op_8xy2(uint16_t opcode, struct Core* core_ptr); // and  <Vx>, <Vy>
void op_8xy3(uint16_t opcode, struct Core* core_ptr); // xor  <Vx>, <Vy>
void op_8xy4(uint16_t opcode, struct Core* core_ptr); // add  <Vx>, <Vy>
void op_8xy5(uint16_t opcode, struct Core* core_ptr); // sub  <Vx>, <Vy>
void op_8xy6(uint16_t opcode, struct Core* core_ptr); // shr  <Vx> (, <Vy>)
void op_8xy7(uint16_t opcode, struct Core* core_ptr); // subn <Vx>, <Vy>
void op_8xye(uint16_t opcode, struct Core* core_ptr); // shl  <Vx> (, <Vy>)
void op_9xy0(uint16_t opcode, struct Core* core_ptr); // sne  <Vx>, <Vy>
void op_annn(uint16_t opcode, struct Core* core_ptr); // ld   I, <addr>
void op_bnnn(uint16_t opcode, struct Core* core_ptr); // jp   V0, <addr>
void op_cxkk(uint16_t opcode, struct Core* core_ptr); // rnd  <Vx>, <byte>
void op_dxyn(uint16_t opcode, struct Core* core_ptr); // drw  <Vx>, <Vy>, <nibble>
void op_ex9e(uint16_t opcode, struct Core* core_ptr); // skp  <Vx>
void op_exa1(uint16_t opcode, struct Core* core_ptr); // sknp <Vx>
void op_fx07(uint16_t opcode, struct Core* core_ptr); // ld   <Vx>, DT
void op_fx0a(uint16_t opcode, struct Core* core_ptr); // ld   <Vx>, K
void op_fx15(uint16_t opcode, struct Core* core_ptr); // ld   DT, <Vx>
void op_fx18(uint16_t opcode, struct Core* core_ptr); // ld   ST, <Vx>
void op_fx1e(uint16_t opcode, struct Core* core_ptr); // add  I, <Vx>
void op_fx29(uint16_t opcode, struct Core* core_ptr); // ld   F, <Vx>
void op_fx33(uint16_t opcode, struct Core* core_ptr); // ld   B, <Vx>
void op_fx55(uint16_t opcode, struct Core* core_ptr); // ld   [I], <Vx>
void op_fx65(uint16_t opcode, struct Core* core_ptr); // ld   <Vx>, [I]
void op_ukwn(uint16_t opcode);                        // unknown

#endif
