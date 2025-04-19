
#
# Makefile for lab7, part2
#

http-server: http-server.o
	gcc -g http-server.o

http-server.o:
	gcc -g -Wall http-server.c

.PHONY:
clean:
	rm -rf *~
	rm -rf *.o
	rm -rf core
	rm -rf http-server

.PHONY: all
all: clean http-server

