
#
# Makefile for lab6, part1
#

CC  = gcc
CXX = g++

INCLUDES = -I../../lab3/solutions/part1
CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g -L../../lab3/solutions/part1
LDLIBS = -lmylist

mdb-lookup-server: mdb-lookup-server.o 

# header dependency
mdb-lookup-server.o: mdb.h

.PHONY: clean
clean:
	rm -rf *.o *~ a.out core mdb-lookup-server

.PHONY: all
all: clean mdb-lookup-server

