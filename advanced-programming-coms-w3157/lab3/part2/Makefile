CC  = gcc

INCLUDES = -I../part1

CFLAGS   = -g -Wall $(INCLUDES)

LDFLAGS = -g -L../part1

LDLIBS = -lmylist

revecho: revecho.o

.PHONY: clean
clean:
	rm -f *.o a.out core revecho

.PHONY: all
all: clean revecho
