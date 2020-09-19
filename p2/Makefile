CC = gcc
CFLAGS = -Wall -std=c99 -g

blur.o: blur.c
border.o: border.c
brighten.o: brighten.c
image.o: image.c image.h
blur: blur.o image.o
	$(CC) $(CFLAGS) image.o blur.o -o blur
border: border.o image.o
	$(CC) $(CFLAGS) image.o border.o -o border
brighten: brighten.o image.o
	$(CC) $(CFLAGS) image.o brighten.o -o brighten
clean: 
	rm -f *.o
	rm -f output.ppm
	rm brighten
	rm border
	rm blur