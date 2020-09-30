CC = gcc
CFLAGS = -Wall -std=c99 -g

chop: text.o edit.o chop.c
	$(CC) $(CFLAGS) text.o edit.o chop.c -o chop
text.o: text.c text.h
edit.o: edit.c edit.h
clean: 
	rm -f *.o
	rm -f output.txt
	rm chop
	rm -f stderr.txt
	rm -f stdout.txt