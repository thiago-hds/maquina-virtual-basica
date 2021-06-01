#include "instructions_info.h"

const char *INSTRUCTION_SYMBOLS[NUMBER_OF_INSTRUCTIONS] = {
    "HALT",     // 00
    "LOAD",     // 01
    "STORE",    // 02
    "READ",     // 03
    "WRITE",    // 04
    "COPY",     // 05
    "PUSH",     // 06
    "POP",      // 07
    "JUMP",     // 08
    "JZ",       // 09
    "JNZ",      // 10
    "JN",       // 11
    "JNN",      // 12
    "CALL",     // 13
    "RET",      // 14
    "AND",      // 15
    "OR",       // 16
    "NOT",      // 17
    "XOR",      // 18
    "ADD",      // 19
    "SUB",      // 20
    "MUL",      // 21
    "DIV",      // 22
    "MOD",      // 23
    "CMP",      // 24
    "TST"       // 25
};
const int INSTRUCTION_NUMBER_OF_OPERANDS[NUMBER_OF_INSTRUCTIONS] = {
    0,          // 00
    2,          // 01
    2,          // 02
    1,          // 03
    1,          // 04
    2,          // 05
    1,          // 06
    1,          // 07
    1,          // 08
    1,          // 09
    1,          // 10
    1,          // 11
    1,          // 12
    1,          // 13
    0,          // 14
    2,          // 15
    2,          // 16
    1,          // 17
    2,          // 18
    2,          // 19
    2,          // 20
    2,          // 21
    2,          // 22
    2,          // 23
    2,          // 24
    2           // 25
};