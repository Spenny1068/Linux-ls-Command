# the compiler: gcc or g++
CC = gcc

# compiler flags:
CFLAGS = -Wall

# create executable
all: main.o list.o
	$(CC) $(CFLAGS) -o main main.o list.o 

# create main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm main.o main
