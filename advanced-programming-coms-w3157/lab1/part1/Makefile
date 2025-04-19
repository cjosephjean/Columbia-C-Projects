CC = gcc
CFLAGS = -g -Wall

main: main.o gcd.o prime.o
	gcc main.o gcd.o prime.o -lm -o main 
	
main.o: main.c prime.h gcd.h
	gcc -c -g -Wall main.c

gcd.o: gcd.c gcd.h
	gcc -c -g -Wall gcd.c

prime.o: prime.c prime.h
	gcc -c -g -Wall prime.c

.PHONY: clean
clean: 
	rm -f *.o
	rm -f main
	rm -f *~

.PHONY: all
all:	clean main
