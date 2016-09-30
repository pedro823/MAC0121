.PHONY = clean
.DELETE_ON_ERROR:
$(CC) = gcc
$(cflags) = -Wall -ansi -pedantic -O2
ep3: circularVector.o ep3.o
	$(CC) -o $@ $^ $(cflags)

ep3debug: circularVector.o ep3.o
	$(CC) -o $@ $^ $(cflags) -g 

circularVector.o: circularVector.h circularVector.c
	$(CC) $^ -c
	
ep3.o: ep3.c
	$(CC) $^ -c
	
clean:
	rm -f *.o *.gch ep2
