CC = gcc
CFLAGS = -Wall -std=c99 -g

reading: catalog.o input.o reading.o
	$(CC) $(CFLAGS) catalog.o input.o reading.o -o reading
reading.o: reading.c
catalog.o: catalog.c catalog.h
input.o: input.c input.h
clean: 
	rm -f *.o
	rm -f output.txt
	rm reading
	rm -f stderr.txt
	rm -f stdout.txt
