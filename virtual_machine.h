#ifndef __VIRTUAL_MACHINE_H__
#define __VIRTUAL_MACHINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1000

#define B00 0
#define B01 1
#define B10 2

int DEBUG_MODE;

// memoria e registradores
int MEMORY[MEMORY_SIZE];
int GENERAL_REGISTERS[4];
int PC;
int AP;
int PEP;

// instrucoes
void halt();
void load(int r, int m);
void store(int r, int m);
void read(int r);
void write(int r);
void copy (int r1, int r2);
void push(int r);
void pop(int r);
void jump(int m);
void jz(int m);
void jnz(int m);
void jumpn(int m);
void jnn(int m);
void call(int m);
void ret();
void and(int r1, int r2);
void or(int r1, int r2);
void not(int r1);
void xor(int r1, int r2);
void add(int r1, int r2);
void sub(int r1, int r2);
void mul(int r1, int r2);
void division(int r1, int r2);
void mod(int r1, int r2);
void cmp(int r1, int r2);
void tst(int r1, int r2);

void updatePEP(int result);
void dumpRegisters();
void execute(int code, int* operands);

#endif