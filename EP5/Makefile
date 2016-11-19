.PHONY=clean
.DELETE_ON_ERROR=
$(CC) := gcc
CFLAGS := -Wall -ansi -pedantic -O2 -g

ep5: hex.o queue.o positionHandler.o strategy.o
	$(CC) $^ -o $@
	rm *.o *.gch

%.o: %.c
	$(CC) $^ $(CFLAGS) -c

clean:
	rm -f *.o *.gch ep5
