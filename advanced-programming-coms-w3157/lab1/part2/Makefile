convert: convert.o
	gcc -g convert.o -o convert

convert.o: convert.c
	gcc -c -g -Wall convert.c

.PHONY: clean
clean:
	rm -f *.o convert *~

.PHONY: all
all: clean convert
