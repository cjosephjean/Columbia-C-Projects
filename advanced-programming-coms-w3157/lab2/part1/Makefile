isort: isort.o sort.o
	gcc -g isort.o sort.o -o isort

isort.o: isort.c sort.h
	gcc -c -g -Wall isort.c

sort.o: sort.c sort.h
	gcc -c -g -Wall sort.c

.PHONY:
clean:
	rm -rf *~
	rm -rf *.o
	rm -rf core
	rm -rf isort

.PHONY:
all:	clean isort
