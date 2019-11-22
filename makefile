
output: main.o tabuleiro.o
	gcc main.o tabuleiro.o -o main

main.o: main.c
	gcc -c main.c

tabuleiro.o: tabuleiro.c tabuleiro.h
	gcc -c tabuleiro.c

clean: 
	rm *.o
