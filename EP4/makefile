.PHONY=clean
$(CC)=gcc
.DELETE_ON_ERROR=
CFLAGS=-Wall -ansi -pedantic -O2
ep4: frequency.o stable.o
	$(CC) $^ -o $@
	rm -f $^

frequency.o: frequency.c
	$(CC) $^ $(CFLAGS) -c

stable.o: stable.h stable.c
	$(CC) $^ $(CFLAGS) -c

clean:
	rm -f *.o ep4
