CC = gcc
flags = -g -std=c11
file = Reader.c
obj = SWIFFT.o

all: $(obj) swifft

SWIFFT.o: SWIFFT.c SWIFFT.h
	$(CC) $(flags) -c SWIFFT.c -o SWIFFT.o

swifft: Reader.c SWIFFT.o
	$(CC) $(file) $(obj) $(flags) -o swifft

clean:
	rm *.o swifft
