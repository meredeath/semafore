all: control.o main.o
	gcc -o control control.o
	gcc -o main main.o
control.o: control.c
	gcc -c control.c
main.o: main.c
	gcc -c main.c
