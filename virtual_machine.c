#include "virtual_machine.h"
#include "instructions_info.h"

// 00 - HALT - Parada
void halt(){
    if(DEBUG_MODE) 
        printf("HALT\n");

    exit(0);
}

// 01 - LOAD R M - Carrega Registrador
void load(int r, int m){
    if(DEBUG_MODE)
        printf("LOAD %d %d\n", r, m);

    GENERAL_REGISTERS[r] = MEMORY[m + PC];
}

// 02 - STORE R M - Armazena Registrador
void store(int r, int m){
    if(DEBUG_MODE)
        printf("STORE %d %d\n", r, m);

    MEMORY[m + PC] = GENERAL_REGISTERS[r];
}

// 03 - READ R - Le valor para registrador
void read(int r){
    if(DEBUG_MODE)
        printf("READ %d\n", r);
    
    scanf("%d", &GENERAL_REGISTERS[r]);
}

// 04 - WRITE R - Escreve conteudo do registrador
void write(int r){
    if(DEBUG_MODE)
        printf("WRITE %d\n", r);

    printf("%d\n", GENERAL_REGISTERS[r]);
}

// 05 - COPY R1 R2 - Copia Registrador
void copy (int r1, int r2){
    if(DEBUG_MODE)
        printf("COPY %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] = GENERAL_REGISTERS[r2];
    
    updatePEP(GENERAL_REGISTERS[r1]);
}

// 06 - PUSH R - Empilha valor do registrador
void push(int r){
    if(DEBUG_MODE)
        printf("PUSH %d\n", r);

    AP -= 1;
    MEMORY[AP] = GENERAL_REGISTERS[r];
}

// 07 - POP R - Desempilha valor no registrador
void pop(int r){
    if(DEBUG_MODE)
        printf("PUSH %d\n", r);

    GENERAL_REGISTERS[r] = MEMORY[AP];
    AP += 1;
}

// 08 - JUMP M - Desvio incondicional
void jump(int m){
    if(DEBUG_MODE)
        printf("JUMP %d\n", m);

    PC += m;
}

// 09 - JZ M - Desvia se zero
void jz(int m){
    if(DEBUG_MODE)
        printf("JZ %d\n", m);

    if((PEP & B10) == B10){
        PC += m;
    }
}

// 10 - JNZ M - Desvia se não zero
void jnz(int m){
    if(DEBUG_MODE)
        printf("JNZ %d\n", m);

    if((PEP & B10) == B00){
        PC += m;
    }
}

// 11 - JN M - Desvia se negativo
void jumpn(int m){
    if(DEBUG_MODE)
        printf("JN %d\n", m);

    if((PEP & B01) == B01){
        PC += m;
    }
}

// 12 - JNN M - Desvia se não negativo
void jnn(int m){
    if(DEBUG_MODE)
        printf("JNN %d\n", m);

    if((PEP & B01) == B00){
        PC += m;
    }
}

// 13 - CALL M - Chamada de subrotina
void call(int m){
    if(DEBUG_MODE)
        printf("CALL %d\n", m);

    AP -= 1;
    MEMORY[AP] = PC;
    PC = PC + m;
}

// 14 - RET - Retorno de subrotina
void ret(){
    if(DEBUG_MODE)
        printf("RET\n");

    PC = MEMORY[AP];
    AP += 1;
}

// 15 - AND R1 R2 - AND (bit a bit) de dois registradores
void and(int r1, int r2){
    if(DEBUG_MODE)
        printf("AND %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] = GENERAL_REGISTERS[r1] & GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 16 - OR R1 R2 - OR (bit a bit) de dois registradores
void or(int r1, int r2){
    if(DEBUG_MODE)
        printf("OR %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] = GENERAL_REGISTERS[r1] | GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 17 - NOT R1 - NOT (bit a bit) de um registrador
void not(int r1){
    if(DEBUG_MODE)
        printf("NOT %d\n", r1);

    GENERAL_REGISTERS[r1] = ~ GENERAL_REGISTERS[r1];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 18 - XOR R1 R2 - XOR (bit a bit) de dois registradores
void xor(int r1, int r2){
    if(DEBUG_MODE)
        printf("XOR %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] = GENERAL_REGISTERS[r1] ^ GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 19 - ADD R1 R2 - Soma dois registradores
void add(int r1, int r2){
    if(DEBUG_MODE)
        printf("ADD %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] += GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 20 - SUB R1 R2 - Subtrai dois registradores
void sub(int r1, int r2){
    if(DEBUG_MODE)
        printf("SUB %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] -= GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 21 - MUL R1 R2 - Multiplica dois registradores
void mul(int r1, int r2){
    if(DEBUG_MODE)
        printf("MUL %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] *= GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 22 - DIV R1 R2 - Dividendo entre dois registradores
void division(int r1, int r2){
    if(DEBUG_MODE)
        printf("DIV %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] /= GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 23 - MOD R1 R2 - Resto entre dois registradores
void mod(int r1, int r2){
    if(DEBUG_MODE)
        printf("MOD %d %d\n", r1, r2);

    GENERAL_REGISTERS[r1] %=  GENERAL_REGISTERS[r2];

    updatePEP(GENERAL_REGISTERS[r1]);
}

// 24 - CMP R1 R2 - Compara dois registradores
void cmp(int r1, int r2){
    if(DEBUG_MODE)
        printf("CMP %d %d\n", r1, r2);

    updatePEP(GENERAL_REGISTERS[r1] - GENERAL_REGISTERS[r2]);
}

// 25 - TST R1 R2 - Testa dois registradores
void tst(int r1, int r2){
    if(DEBUG_MODE)
        printf("TST %d %d\n", r1, r2);

    updatePEP(GENERAL_REGISTERS[r1] & GENERAL_REGISTERS[r2]);
}

void updatePEP(int result){ 
    PEP = B00;
    if(result == 0){
        PEP = B10;
    }
    else if(result < 0){
        PEP = B01;
    }
}

void dumpRegisters(){
    printf("-- REGISTERS --\n"); 
    printf("PC:%d\nAP:%d\nPEP:%d\n", PC, AP, PEP);
    int i;
    for(i=0;i<4;i++){
        printf("REG %d: %d\n", i, GENERAL_REGISTERS[i]);
    }
    printf("--- --- ---\n\n");
}

void execute(int code, int* operands){
    switch(code){
        case HALT:
            halt();
            break;

        case LOAD:
            load(operands[0], operands[1]);
            break;

        case STORE:
            store(operands[0], operands[1]);
            break;

        case READ:
            read(operands[0]);
            break;

        case WRITE:
            write(operands[0]);
            break;

        case COPY:
            copy (operands[0], operands[1]);
            break;

        case PUSH:
            push(operands[0]);
            break;

        case POP:
            pop(operands[0]);
            break;

        case JUMP:
            jump(operands[0]);
            break;

        case JZ:
            jz(operands[0]);
            break;

        case JNZ:
            jnz(operands[0]);
            break;

        case JN:
            jumpn(operands[0]);
            break;

        case JNN:
            jnn(operands[0]);
            break;

        case CALL:
            call(operands[0]);
            break;

        case RET:
            ret();
            break;

        case AND:
            and(operands[0], operands[1]);
            break;

        case OR:
            or(operands[0], operands[1]);
            break;

        case NOT:
            not(operands[0]);
            break;

        case XOR:
            xor(operands[0], operands[1]);
            break;

        case ADD:
            add(operands[0], operands[1]);
            break;

        case SUB:
            sub(operands[0], operands[1]);
            break;

        case MUL:
            mul(operands[0], operands[1]);
            break;

        case DIV:
            division(operands[0], operands[1]);
            break;

        case MOD:
            mod(operands[0], operands[1]);
            break;

        case CMP:
            cmp(operands[0], operands[1]);
            break;

        case TST:
            tst(operands[0], operands[1]);
            break;
    }

    if(DEBUG_MODE)
        dumpRegisters();
}