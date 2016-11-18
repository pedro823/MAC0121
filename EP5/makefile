.PHONY=clean
.DELETE_ON_ERROR=
$(CC) := gcc
CFLAGS := -Wall -ansi -pedantic -O2

ep5: ep5.o stack.o positionHandler.o
	$(CC) $^ -o $@
	rm *.o *.gch

%.o: %.c
	$(CC) $^ $(CFLAGS) -c

clean:
	rm -f *.o *.gch ep5
