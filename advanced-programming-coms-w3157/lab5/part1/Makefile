.PHONY: default
default: mdb-lookup-server-nc-1 mdb-lookup-server-nc-2

mdb-lookup-server-nc-2: mdb-lookup-server-nc-2.o 
	gcc -g mdb-lookup-server-nc-2.o -o mdb-lookup-server-nc-2

mdb-lookup-server-nc-1: mdb-lookup-server-nc-1.o
	gcc -g mdb-lookup-server-nc-1.o -o mdb-lookup-server-nc-1

mdb-lookup-server-nc-1.o: mdb-lookup-server-nc-1.c
	gcc -c -g -Wall mdb-lookup-server-nc-1.c

mdb-lookup-server-nc-2.0: mdb-lookup-server-nc.2.c
	gcc -c -g -Wall mdb-lookup-server-nc-2.c

.PHONY:
clean:
	rm -rf *.o 
	rm -rf core 
	rm -rf *~
	rm -rf mdb-lookup-server-nc-1
	rm -rf mdb-lookup-server-nc-2

.PHONY:
all: clean default
