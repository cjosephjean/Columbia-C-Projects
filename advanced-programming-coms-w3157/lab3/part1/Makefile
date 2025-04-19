mylist-test: mylist.o  mylist-test.o libmylist.a
	gcc -g mylist.o mylist-test.o mylist.h -o mylist-test

libmylist.a: mylist.o
	ar rc  libmylist.a mylist.o
	ranlib libmylist.a

mylist.o: mylist.c mylist.h
	gcc -c -g -Wall mylist.c mylist.h

mylist-test.o: mylist-test.c mylist.h
	gcc -c -g -Wall mylist-test.c mylist.h

.PHONY: clean
clean:	
	rm -rf *.o
	rm -rf core
	rm -f *.a
	rm -rf *~
	rm -rf mylist-test
	rm -rf mylist.h.gch

.PHONY: all
all: clean mylist-test
