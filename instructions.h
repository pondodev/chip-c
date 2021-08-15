#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

void execute_instruction(uint16_t opcode);

// opcode transforms
void get_nibbles(uint16_t opcode, uint8_t* out);
void process_op_5xxx(uint16_t opcode);
void process_op_8xxx(uint16_t opcode);
void process_op_9xxx(uint16_t opcode);
void process_op_9xxx(uint16_t opcode);
void process_op_exxx(uint16_t opcode);
void process_op_fxxx(uint16_t opcode);

// instruction definitions, based off cowgod's chip8 reference
void op_00e0();                // cls
void op_00ee();                // ret
void op_0nnn(uint16_t opcode); // sys  <addr>
void op_1nnn(uint16_t opcode); // jp   <addr>
void op_2nnn(uint16_t opcode); // call <addr>
void op_3xkk(uint16_t opcode); // se   <Vx>, <byte>
void op_4xkk(uint16_t opcode); // sne  <Vx>, <byte>
void op_5xy0(uint16_t opcode); // se   <Vx>, <Vy>
void op_6xkk(uint16_t opcode); // ld   <Vx>, <byte>
void op_7xkk(uint16_t opcode); // add  <Vx>, <byte>
void op_8xy0(uint16_t opcode); // ld   <Vx>, <Vy>
void op_8xy1(uint16_t opcode); // or   <Vx>, <Vy>
void op_8xy2(uint16_t opcode); // and  <Vx>, <Vy>
void op_8xy3(uint16_t opcode); // xor  <Vx>, <Vy>
void op_8xy4(uint16_t opcode); // add  <Vx>, <Vy>
void op_8xy5(uint16_t opcode); // sub  <Vx>, <Vy>
void op_8xy6(uint16_t opcode); // shr  <Vx> (, <Vy>)
void op_8xye(uint16_t opcode); // shl  <Vx> (, <Vy>)
void op_9xy0(uint16_t opcode); // sne  <Vx>, <Vy>
void op_annn(uint16_t opcode); // ld   I, <addr>
void op_bnnn(uint16_t opcode); // jp   V0, <addr>
void op_cxkk(uint16_t opcode); // rnd  <Vx>, <byte>
void op_dxyn(uint16_t opcode); // drw  <Vx>, <Vy>, <nibble>
void op_ex9e(uint16_t opcode); // skp  <Vx>
void op_exa1(uint16_t opcode); // sknp <Vx>
void op_fx07(uint16_t opcode); // ld   <Vx>, DT
void op_fx0a(uint16_t opcode); // ld   <Vx>, K
void op_fx15(uint16_t opcode); // ld   DT, <Vx>
void op_fx18(uint16_t opcode); // ld   ST, <Vx>
void op_fx1e(uint16_t opcode); // add  I, <Vx>
void op_fx29(uint16_t opcode); // ld   F, <Vx>
void op_fx33(uint16_t opcode); // ld   B, <Vx>
void op_fx55(uint16_t opcode); // ld   [I], <Vx>
void op_fx65(uint16_t opcode); // ld   <Vx>, [I]
void op_ukwn(uint16_t opcode); // unknown

#endif
