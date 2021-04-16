all: main

main: functions.o area.o
	gcc -m32 area.o functions.o

area.o: area.c
	gcc -m32 -c area.c -o area.o

functions.o: functions.asm
	nasm -g -f elf32 functions.asm -o functions.o

clean:
	rm -rf *.o
	rm -rf a.out
