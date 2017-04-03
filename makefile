CC = gcc
flags = -g -std=c11 -mavx2 -msse4 -lpthread
file = Reader.c
obj = swifft.o

all: $(obj) swifft

swifft.o: swifft.c swifft.h
	$(CC) $(flags) -c swifft.c -o swifft.o

swifft: Reader.c swifft.o
	$(CC) $(file) $(obj) $(flags) -o swifft

clean:
	rm *.o swifft
