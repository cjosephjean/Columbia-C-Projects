twecho: twecho.o 
	gcc -g twecho.o -o twecho

twecho.o: twecho.c
	gcc -c -g -Wall twecho.c
	
.PHONY:
clean:
	rm -rf *~
	rm -rf *.o
	rm -rf core
	rm -rf twecho

.PHONY:
all:	clean twecho
