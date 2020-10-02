CC = gcc
CFLAGS = -Wall -std=c99 -g

chop: text.o edit.o chop.o
	$(CC) $(CFLAGS) text.o edit.o chop.o -o chop
chop.o: chop.c
text.o: text.c text.h
edit.o: edit.c edit.h
clean: 
	rm -f *.o
	rm -f output.txt
	rm chop
	rm -f stderr.txt
	rm -f stdout.txt