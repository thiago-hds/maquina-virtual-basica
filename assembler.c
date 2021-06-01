#include "instructions_info.h"
#include <stdio.h>
#include <string.h>

#define DEFAULT_LOAD_ADDRESS 100
#define DEFAULT_STACK_POINTER 999
#define MAX_BUFFER_SIZE 30
#define MAX_SYMBOLS 100

int getRegisterNumber(char *reg){
    if(strcmp(reg, "R0") == 0){
        return 0;
    }
    else if(strcmp(reg, "R1") == 0){
        return 1;
    }
    else if(strcmp(reg, "R2") == 0){
        return 2;
    }
    else if(strcmp(reg, "R3") == 0){
        return  3;
    }

    return -1;
}

int getCode(char *symbol){
    int i;
    for(i=0;i<NUMBER_OF_INSTRUCTIONS;i++){
        if(strcmp(INSTRUCTION_SYMBOLS[i], symbol) == 0){
            return i;
        }
    }

    return -1;
}

int main(int argc, char *argv[]){
    char *fileName;
    int instructionLocationCounter = 0;

    char symbols[MAX_SYMBOLS][MAX_BUFFER_SIZE];
    int symbolsLocation[MAX_SYMBOLS];
    int symbolsCounter = 0;

    int words[MAX_SYMBOLS];
    int wordsCounter = 0;

    int instructionCode;
    int instructionNumberOperands;

    int registerNumber;
    char buffer[MAX_BUFFER_SIZE];
    char c;
    int end = 0;
    int i,j;

    if(argc == 2){
        fileName = argv[1];
    }

    FILE *file;
    file = fopen(fileName, "r");

    // PRIMEIRA PASSAGEM
    while(!feof(file) && !end){
        fscanf(file, "%s", buffer);

        // label
        if(buffer[strlen(buffer) - 1] == ':'){
            buffer[strlen(buffer) - 1] = '\0';
            strcpy(symbols[symbolsCounter], buffer);
            symbolsLocation[symbolsCounter] = instructionLocationCounter;
            symbolsCounter ++;
        }

        // comentario
        else if(buffer[0] == ';'){
            c = 'a';
            while(c != '\n'){
                fscanf(file, "%c", &c);
            }
        }

        // operador ou operando
        else{
            if((strcmp(buffer, "END") == 0)){
                end = 1;
            }
            else if((strcmp(buffer, "WORD") != 0)){
                instructionLocationCounter ++;
            }
        }
    }

    printf("MV-EXE\n");
    printf("%d %d %d %d\n",
        instructionLocationCounter, DEFAULT_LOAD_ADDRESS, DEFAULT_STACK_POINTER, DEFAULT_LOAD_ADDRESS);
    fseek(file, 0, SEEK_SET);
    instructionLocationCounter = 0;
    end = 0;

    // SEGUNDA PASSAGEM
    while(!feof(file) && !end){
        fscanf(file, "%s", buffer);

        // comentario
        if(buffer[0] == ';'){
            c = 'a';
            while(c != '\n'){
                fscanf(file, "%c", &c);
            }
        }

        // operador ou operando
        else if(buffer[strlen(buffer) - 1] != ':'){

            // reservar posicao de memoria
            if(strcmp(buffer, "WORD") == 0){
                fscanf(file, "%d", &words[wordsCounter]);
                wordsCounter ++;
            }

            // fim do programa
            else if(strcmp(buffer, "END") == 0){
                end = 1;
            }

            // instrucao
            else{
                instructionCode = getCode(buffer);
                instructionNumberOperands = INSTRUCTION_NUMBER_OF_OPERANDS[instructionCode];

                printf("%d ", instructionCode);

                for(i=0;i<instructionNumberOperands;i++){
                    fscanf(file, "%s", buffer);

                    registerNumber = getRegisterNumber(buffer);

                    // operando eh registrador
                    if(registerNumber != -1){
                        printf("%d ", registerNumber);
                    }

                    // operando eh simbolo
                    else{
                        // buscar na tabela de simbolos
                        j = 0;
                        while(strcmp(symbols[j], buffer) != 0){
                            j++;
                        }

                        // calcular a posicao do valor na memoria em relacao ao ILC
                        printf ("%d ", symbolsLocation[j]
                            - (instructionLocationCounter + 1 + instructionNumberOperands));
                    }   
                }
                
                instructionLocationCounter += 1 + instructionNumberOperands;
            }
        }
    }

    // posicoes reservadas da memoria
    for(i=0;i<wordsCounter;i++){
        printf("%d\n", words[i]);
    }

    fclose(file);

    return 0;
}