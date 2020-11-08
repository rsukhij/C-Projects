CC = gcc
CFLAGS = -Wall -std=c99 -g


hash: hash.o sha1.o buffer.o hmac-sha1.o
	$(CC) $(CFLAGS) hash.o sha1.o buffer.o hmac-sha1.o -o hash
testdriver: testdriver.o hash.o sha1.o buffer.o
	$(CC) $(CFLAGS) -DTESTABLE testdriver.c sha1.c buffer.c -o testdriver
testdriver.o : testdriver.c
hash.o: hash.c
sha1.o: sha1.c sha1.h
buffer.o: buffer.c buffer.h
hmac-sha1.o: hmac-sha1.c hmac-sha1.h

clean: 
	rm -f *.o
	rm -f output.txt
	rm -f stderr.txt
	rm -f stdout.txt
