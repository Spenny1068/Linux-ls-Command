# the compiler: gcc or g++
CC = gcc

# compiler flags:
CFLAGS = -Wall

# create executable
all: UnixLs.o
	$(CC) $(CFLAGS) -o UnixLs UnixLs.o

# create UnixLs.o
UnixLs.o: UnixLs.c
	$(CC) $(CFLAGS) -c UnixLs.c

clean:
	rm UnixLs.o UnixLs
