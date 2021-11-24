run: main.out
	./main.out

main.out: main.o
	gcc main.o -o main.out
	rm main.o

main.o: main.c
	gcc -c main.c