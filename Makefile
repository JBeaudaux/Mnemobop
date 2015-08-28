sources=./src/mnemobop.cpp
sources+=./src/common/common.cpp
sources+=./src/flashcards/carddeck.cpp

headers=./src/common/common.h

objects=$(sources:.cpp=.o)

modules	:= ./src
modules	+= ./src/common
modules	+= ./src/flashcards

CC=g++
CFLAGS=-I.

mnemobop: $(objects)
	$(CC) -o $@ $^

mnemobop.o: ./src/mnemobop.cpp
	$(CC) -Wall -c $^

common.o: ./src/common/common.cpp
	$(CC) -Wall -c $^

clean:
	rm -f *.o

mrproper:
	rm -f mnemobop
