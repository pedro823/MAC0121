.PHONY = clean
$(CC) = gcc
ep3: circularVector.o ep3.o
	$(CC) -o $@ $^

circularVector.o: circularVector.h circularVector.c
	$(CC) $^ -c
	
ep3.o: ep3.c
	$(CC) $^ -c
	
clean:
	rm -f *.o *.gch ep2
