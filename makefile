CC = gcc
file = Reader.c
obj = SWIFFT.o

all: $(obj) swifft

SWIFFT.o: SWIFFT.c SWIFFT.h
	$(CC) -g -c SWIFFT.c -o SWIFFT.o

swifft: Reader.c SWIFFT.o
	$(CC) $(file) $(obj) -g -o swifft -lgmp

clean:
	rm *.o swifft
