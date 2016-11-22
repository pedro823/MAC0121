.PHONY: clean
.DELETE_ON_ERROR:
$(CC) := gcc
CFLAGS := -Wall -ansi -pedantic -O2 -g

ep5: hex.o queue.o positionHandler.o strategy.o
	$(CC) $^ -o $@
	rm -f *.o *.gch

%.o: %.c
	$(CC) $^ $(CFLAGS) -c

clean:
	rm -f *.o *.gch ep5

tester: strategy.o strategytester.o positionHandler.o queue.o
	$(CC) $^ -o $@
