CC = g++
CFLAGS = -g -Wall

all: inst

inst: main.o instructionHandler.o
	$(CC) $(CFLAGS) -o inst main.o instructionHandler.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

instructionHandler.o: instructionHandler.cpp instructionHandler.h
	$(CC) $(CFLAGS) -c instructionHandler.cpp

clean:
	rm *.o inst