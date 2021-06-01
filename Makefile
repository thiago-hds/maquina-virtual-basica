all: emulator assembler
emulator: emulator.o virtual_machine.o instructions_info.o
	gcc emulator.o virtual_machine.o instructions_info.o -Wall -Wextra -Werror -std=c99 -pedantic -o emulator
assembler: assembler.o instructions_info.o
	gcc assembler.o instructions_info.o -Wall -Wextra -Werror -std=c99 -pedantic -o assembler
emulator.o: emulator.c
	gcc -g -Wall -Wextra -Werror -std=c99 -pedantic -c emulator.c
assembler.o: assembler.c
	gcc -g -Wall -Wextra -Werror -std=c99 -pedantic -c assembler.c
virtual_machine.o: virtual_machine.c
	gcc -g -Wall -Wextra -Werror -std=c99 -pedantic -c virtual_machine.c
instructions_info.o: instructions_info.h
	gcc -g -Wall -Wextra -Werror -std=c99 -pedantic -c instructions_info.c

clean:
	rm *.o
	rm emulator
	rm assembler