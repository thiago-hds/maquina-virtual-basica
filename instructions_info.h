#ifndef __INSTRUCTIONS_INFO_H__
#define __INSTRUCTIONS_INFO_H__

#define HALT 0
#define LOAD 1
#define STORE 2
#define READ 3
#define WRITE 4
#define COPY 5
#define PUSH 6
#define POP 7
#define JUMP 8
#define JZ 9
#define JNZ 10
#define JN 11
#define JNN 12
#define CALL 13
#define RET 14
#define AND 15
#define OR 16
#define NOT 17
#define XOR 18
#define ADD 19
#define SUB 20
#define MUL 21
#define DIV 22
#define MOD 23
#define CMP 24
#define TST 25

#define NUMBER_OF_INSTRUCTIONS 26 

extern const char *INSTRUCTION_SYMBOLS[NUMBER_OF_INSTRUCTIONS];
extern const int INSTRUCTION_NUMBER_OF_OPERANDS[NUMBER_OF_INSTRUCTIONS];

#endif