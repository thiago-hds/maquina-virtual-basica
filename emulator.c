#include "instructions_info.h"
#include "virtual_machine.h"
#include <string.h>

#define MAX_BUFFER_SIZE 30

int PROGRAM_SIZE;
int LOAD_ADDRESS;

int loadProgram(char *fileName){
    char line[MAX_BUFFER_SIZE];

    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("arquivo nao encontrado\n");
        return 0;
    }

    if(fgets(line, MAX_BUFFER_SIZE, file) == NULL){
        printf("erro ao ler arquivo\n");
        return 0;
    }

    line[strlen(line) - 1] = '\0';
    if(strcmp(line, "MV-EXE") != 0){
        printf("formato nao executavel\n");
        return 0;
    }
    
    fscanf(file, "%d %d %d %d", &PROGRAM_SIZE, &LOAD_ADDRESS, &AP, &PC);

    // carregar programa para memoria
    int i, currentAddress;
    currentAddress = LOAD_ADDRESS;

    while(currentAddress - LOAD_ADDRESS < PROGRAM_SIZE && !feof(file)){
        fscanf(file, "%d", &i);
        MEMORY[currentAddress] = i;
        currentAddress ++;
    }
    fclose(file);
    return 1;
}

int main(int argc, char *argv[]){

    char *fileName;
    int instruction;
    int *operands;

    DEBUG_MODE = 0;

    if(argc == 2){
         fileName = argv[1];
    }
    else if(argc == 3){
        if(strcmp(argv[1], "-v") == 0){
            DEBUG_MODE = 1;
            fileName = argv[2];
        }
        else if(strcmp(argv[2], "-v") == 0){
            DEBUG_MODE = 1;
            fileName = argv[1];
        }
    }    
  
    if(!loadProgram(fileName)){
        return 1;
    }

    while(PC <= LOAD_ADDRESS + PROGRAM_SIZE){
        instruction = MEMORY[PC];
        operands = &MEMORY[PC + 1];

        PC += INSTRUCTION_NUMBER_OF_OPERANDS[instruction] + 1;
        execute(instruction, operands);
    }  

    return 0;
}