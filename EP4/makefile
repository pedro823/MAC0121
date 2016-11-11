.PHONY=clean
$(CC)=gcc
.DELETE_ON_ERROR=
CFLAGS=-Wall -ansi -pedantic -O2 -pg
ep4: frequency.o stable.o buffer.o
	gcc $^ -o $@
	rm -f $^

frequency.o: frequency.c
	gcc $^ $(CFLAGS) -c

buffer.o: buffer.c
	gcc $^ $(CFLAGS) -c

stable.o: stable.c tabelaSimbolo_LD.c tabelaSimbolo_VD.c tabelaSimbolo_VO.c tabelaSimbolo_LO.c tabelaSimbolo_AB.c
	gcc $^ $(CFLAGS) -c

clean:
	rm -f *.o *.gch ep4
