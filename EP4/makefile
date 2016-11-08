.PHONY=clean
$(CC)=gcc
.DELETE_ON_ERROR=
CFLAGS=-Wall -ansi -pedantic -O2
ep4: frequency.o stable.o buffer.o
	$(CC) $^ -o $@
	rm -f $^

frequency.o: frequency.c
	$(CC) $^ $(CFLAGS) -c

buffer.o: buffer.c
	$(CC) $^ $(CFLAGS) -c

stable.o: stable.c tabelaSimbolo_LD.c tabelaSimbolo_VD.c tabelaSimbolo_VO.c tabelaSimbolo_LO.c tabelaSimbolo_AB.c
	$(CC) $^ $(CFLAGS) -c

clean:
	rm -f *.o *.gch ep4
