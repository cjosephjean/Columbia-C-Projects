http-client: http-client.o
	gcc -g http-client.o -o http-client

http-client.o: http-client.c
	gcc -g -c -Wall http-client.c

.PHONY:
clean: 
	rm -rf *~
	rm -rf core
	rm -rf *.o
	rm -rf http-client

.PHONY:
all: clean http-client
