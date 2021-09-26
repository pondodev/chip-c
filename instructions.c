#include <stdio.h>

#include "instructions.h"

void execute_instruction(uint16_t opcode, struct Core* core_ptr) {
    switch (opcode) {
        case 0x00E0:
            op_00e0(core_ptr);
            break;

        case 0x00EE:
            op_00ee(core_ptr);
            break;

        case 0x0000 ... 0x00DF:
        case 0x00E1 ... 0x00ED:
        case 0x00EF ... 0x0FFF:
            op_0nnn(opcode, core_ptr);
            break;

        case 0x1000 ... 0x1FFF:
            op_1nnn(opcode, core_ptr);
            break;

        case 0x2000 ... 0x2FFF:
            op_2nnn(opcode, core_ptr);
            break;

        case 0x3000 ... 0x3FFF:
            op_3xkk(opcode, core_ptr);
            break;

        case 0x4000 ... 0x4FFF:
            op_4xkk(opcode, core_ptr);
            break;

        case 0x5000:
            process_op_5xxx(opcode, core_ptr);
            break;

        case 0x6000 ... 0x6FFF:
            op_6xkk(opcode, core_ptr);
            break;

        case 0x7000 ... 0x7FFF:
            op_7xkk(opcode, core_ptr);
            break;

        case 0x8000 ... 0x8FFF:
            process_op_8xxx(opcode, core_ptr);
            break;

        case 0x9000 ... 0x9FFF:
            process_op_9xxx(opcode, core_ptr);
            break;

        case 0xA000 ... 0xAFFF:
            op_annn(opcode, core_ptr);
            break;

        case 0xB000 ... 0xBFFF:
            op_bnnn(opcode, core_ptr);
            break;

        case 0xC000 ... 0xCFFF:
            op_cxkk(opcode, core_ptr);
            break;

        case 0xD000 ... 0xDFFF:
            op_dxyn(opcode, core_ptr);
            break;

        case 0xE000 ... 0xEFFF:
            process_op_exxx(opcode, core_ptr);
            break;

        case 0xF000 ... 0xFFFF:
            process_op_fxxx(opcode, core_ptr);
            break;

        default:
            op_ukwn(opcode);
            break;
    }
}

void get_nibbles(uint16_t opcode, uint8_t* out) {
    out[0] = (opcode & 0xF000) >> 12;
    out[1] = (opcode & 0x0F00) >> 8;
    out[2] = (opcode & 0x00F0) >> 4;
    out[3] =  opcode & 0x000F;
}

uint16_t get_address(uint16_t opcode) {
    return opcode & 0x0FFF;
}

void process_op_5xxx(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    switch (nibbles[3]) {
        case 0x0:
            op_5xy0(opcode, core_ptr);
            break;

        default:
            op_ukwn(opcode);
            break;
    }
}

void process_op_8xxx(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    switch (nibbles[3]) {
        case 0x0:
            op_8xy0(opcode, core_ptr);
            break;

        case 0x1:
            op_8xy1(opcode, core_ptr);
            break;

        case 0x2:
            op_8xy2(opcode, core_ptr);
            break;

        case 0x3:
            op_8xy3(opcode, core_ptr);
            break;

        case 0x4:
            op_8xy4(opcode, core_ptr);
            break;

        case 0x5:
            op_8xy5(opcode, core_ptr);
            break;

        case 0x6:
            op_8xy6(opcode, core_ptr);
            break;

        case 0xE:
            op_8xye(opcode, core_ptr);
            break;

        default:
            op_ukwn(opcode);
            break;
    }
}

void process_op_9xxx(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    switch (nibbles[3]) {
        case 0x0:
            op_9xy0(opcode, core_ptr);
            break;

        default:
            op_ukwn(opcode);
            break;
    }
}

void process_op_exxx(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);
    uint8_t byte = nibbles[3];
    byte |= nibbles[2] << 4;

    switch (byte) {
        case 0x9E:
            op_ex9e(opcode, core_ptr);
            break;

        case 0xa1:
            op_exa1(opcode, core_ptr);
            break;

        default:
            op_ukwn(opcode);
            break;
    }
}

void process_op_fxxx(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);
    uint8_t byte = nibbles[3];
    byte |= nibbles[2] << 4;

    switch (byte) {
        case 0x07:
            op_fx07(opcode, core_ptr);
            break;

        case 0x0A:
            op_fx0a(opcode, core_ptr);
            break;

        case 0x15:
            op_fx15(opcode, core_ptr);
            break;

        case 0x18:
            op_fx18(opcode, core_ptr);
            break;

        case 0x1E:
            op_fx1e(opcode, core_ptr);
            break;

        case 0x29:
            op_fx29(opcode, core_ptr);
            break;

        case 0x33:
            op_fx33(opcode, core_ptr);
            break;

        case 0x55:
            op_fx55(opcode, core_ptr);
            break;

        case 0x65:
            op_fx65(opcode, core_ptr);
            break;

        default:
            op_ukwn(opcode);
            break;
    }
}

void op_00e0(struct Core* core_ptr) {
    for (int i = 0; i < VIDEO_SIZE; i++) {
        core_ptr->video[i] = 0x0;
    }
}

void op_00ee(struct Core* core_ptr) {
    core_ptr->pc = core_ptr->stack[core_ptr->sp];
    core_ptr->sp--;
}

void op_0nnn(uint16_t opcode, struct Core* core_ptr) {
    // does nothing
}

void op_1nnn(uint16_t opcode, struct Core* core_ptr) {
    core_ptr->pc = get_address(opcode);
}

void op_2nnn(uint16_t opcode, struct Core* core_ptr) {
    core_ptr->sp++;
    core_ptr->stack[core_ptr->sp] = core_ptr->pc;
    core_ptr->pc = get_address(opcode);
}

void op_3xkk(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t val1 = core_ptr->registers[nibbles[1]];
    uint8_t val2 = (nibbles[2] << 4) | nibbles[3];

    if (val1 == val2) core_ptr->pc += 2;
}

void op_4xkk(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t val1 = core_ptr->registers[nibbles[1]];
    uint8_t val2 = (nibbles[2] << 4) | nibbles[3];

    if (val1 != val2) core_ptr->pc += 2;
}

void op_5xy0(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t val1 = core_ptr->registers[nibbles[1]];
    uint8_t val2 = core_ptr->registers[nibbles[2]];

    if (val1 == val2) core_ptr->pc += 2;
}

void op_6xkk(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);
    uint8_t byte = (nibbles[2] << 4) | nibbles[3];
    core_ptr->registers[nibbles[1]] = byte;
}

void op_7xkk(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);
    uint8_t byte = (nibbles[2] << 4) | nibbles[3];
    core_ptr->registers[nibbles[1]] += byte;
}

void op_8xy0(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    core_ptr->registers[1] = core_ptr->registers[2];
}

void op_8xy1(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    core_ptr->registers[1] |= core_ptr->registers[2];
}

void op_8xy2(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    core_ptr->registers[1] &= core_ptr->registers[2];
}

void op_8xy3(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    core_ptr->registers[1] ^= core_ptr->registers[2];
}

void op_8xy4(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint16_t res = core_ptr->registers[1] + core_ptr->registers[2];
    core_ptr->registers[1] = res & 0x00FF;

    if (res > 0xFF) {
        core_ptr->registers[0xF] = 0x1;
    } else {
        core_ptr->registers[0xF] = 0x0;
    }
}

void op_8xy5(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t* vx = &(core_ptr->registers[nibbles[1]]);
    uint8_t* vy = &(core_ptr->registers[nibbles[1]]);

    if (*vx > *vy) {
        core_ptr->registers[0xF] = 1;
    } else {
        core_ptr->registers[0xF] = 0;
    }

    *vx -= *vy;
}

void op_8xy6(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t* vx = &(core_ptr->registers[nibbles[1]]);
    if (*vx & 0b00000001) core_ptr->registers[0xF] = 1;
    else core_ptr->registers[0xF] = 0;

    *vx = *vx >> 1;
}

void op_8xy7(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t* vx = &(core_ptr->registers[nibbles[1]]);
    uint8_t* vy = &(core_ptr->registers[nibbles[1]]);

    if (*vy > *vx) {
        core_ptr->registers[0xF] = 1;
    } else {
        core_ptr->registers[0xF] = 0;
    }

    *vx -= *vy;
}

void op_8xye(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t* vx = &(core_ptr->registers[nibbles[1]]);
    if (*vx & 0b10000000) core_ptr->registers[0xF] = 1;
    else core_ptr->registers[0xF] = 0;

    *vx = *vx << 1;
}

void op_9xy0(uint16_t opcode, struct Core* core_ptr) {
    uint8_t nibbles[4];
    get_nibbles(opcode, nibbles);

    uint8_t vx = core_ptr->registers[nibbles[1]];
    uint8_t vy = core_ptr->registers[nibbles[1]];

    if (vy != vx) core_ptr->pc += 2;
}

void op_annn(uint16_t opcode, struct Core* core_ptr) {
    uint16_t addr = get_address(opcode);

    core_ptr->index = core_ptr->memory[addr];
}

void op_bnnn(uint16_t opcode, struct Core* core_ptr) {
    uint16_t addr = get_address(opcode);
    uint8_t v0 = core_ptr->registers[0];
    core_ptr->pc = addr + v0;
}

void op_cxkk(uint16_t opcode, struct Core* core_ptr) {
    uint8_t num = rand() % 256;
    uint8_t kk = opcode & 0x00FF;
    uint8_t x = (opcode & 0x0F00) >> 8;

    core_ptr->registers[x] = num & kk;
}

void op_dxyn(uint16_t opcode, struct Core* core_ptr) {
    printf("drw  <Vx>, <Vy>, <nibble>\n");
}

void op_ex9e(uint16_t opcode, struct Core* core_ptr) {
    printf("skp  <Vx>\n");
}

void op_exa1(uint16_t opcode, struct Core* core_ptr) {
    printf("sknp <Vx>\n");
}

void op_fx07(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   <Vx>, DT\n");
}

void op_fx0a(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   <Vx>, K\n");
}

void op_fx15(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   DT, <Vx>\n");
}

void op_fx18(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   ST, <Vx>\n");
}

void op_fx1e(uint16_t opcode, struct Core* core_ptr) {
    printf("add  I, <Vx>\n");
}

void op_fx29(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   F, <Vx>\n");
}

void op_fx33(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   B, <Vx>\n");
}

void op_fx55(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   [I], <Vx>\n");
}

void op_fx65(uint16_t opcode, struct Core* core_ptr) {
    printf("ld   <Vx>, [I]\n");
}

void op_ukwn(uint16_t opcode) {
    printf("unrecognised instruction: 0x%04x\n", opcode);
}
