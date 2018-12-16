all: control.o main.o
	gcc control.o main.o
control.o: control.c
	gcc -c control.c
main.o: main.c
	gcc -c main.c
