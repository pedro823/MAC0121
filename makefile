.PHONY=clean
DELETE_ON_ERROR:
$(CC)=gcc
CFLAGS=-Wall -ansi -pedantic -O2
ep3: circularVector.o tresReversao.o
	$(CC) -o $@ $^ $(CFLAGS)
	rm -f *.o *.gch

ep3debug: circularVector.o ep3.o
	$(CC) -o $@ $^ $(CFLAGS) -g
	rm -f *.o *.gch

circularVector.o: circularVector.h circularVector.c
	$(CC) $^ $(CFLAGS) -c

tresReversao.o: tresReversao.c
	$(CC) $^ $(CFLAGS) -c

clean:
	rm -f *.o *.gch ep3 ep3debug out.txt out
