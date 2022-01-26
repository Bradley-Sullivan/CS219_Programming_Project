CC = g++
CFLAGS = -g -Wall

# all: inst

# inst: main.o instructionHandler.o
# 	$(CC) $(CFLAGS) -o inst main.o instructionHandler.o

# main.o: main.cpp
# 	$(CC) $(CFLAGS) -c main.cpp

# instructionHandler.o: instructionHandler.cpp instructionHandler.h
# 	$(CC) $(CFLAGS) -c instructionHandler.cpp

# clean:
# 	rm *.o inst

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