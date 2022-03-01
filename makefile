CC = g++
CFLAGS = -g -Wall

all: inst

inst: driver.o instructionLoader.o armInstruction.o
	$(CC) $(CFLAGS) -o inst driver.o instructionLoader.o armInstruction.o

driver.o: driver.cpp
	$(CC) $(CFLAGS) -c driver.cpp

instructionHandler.o: instructionLoader.cpp instructionLoader.h
	$(CC) $(CFLAGS) -c instructionLoader.cpp

armInstruction.o: armInstruction.cpp armInstruction.h
	$(CC) $(CFLAGS) -c armInstruction.cpp

clean:
	rm *.o inst