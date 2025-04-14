CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: tarea1

tarea1: main.o enigma.o
	$(CC) $(CFLAGS) -o tarea1 main.o enigma.o

main.o: main.c enigma.h
	$(CC) $(CFLAGS) -c main.c

enigma.o: enigma.c enigma.h
	$(CC) $(CFLAGS) -c enigma.c

clean:
	rm -f *.o tarea1
