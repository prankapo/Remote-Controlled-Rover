run: main.out
	./main.out

main.out: main.o
	gcc main.o -o main.out

main.o: main.c
	gcc -c main.c