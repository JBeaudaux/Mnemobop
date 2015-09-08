sources=./src/mnemobop.cpp
sources+=./src/common/common.cpp
sources+=./src/flashcards/carddeck.cpp
sources+=./src/graphics/graphics.cpp

headers=./src/common/common.h

objects=$(sources:.cpp=.o)

modules	:= ./src
modules	+= ./src/common
modules	+= ./src/flashcards

CC=g++
CPPFLAGS = -I.
CPPFLAGS += -I/usr/include/gtk-3.0/
CPPFLAGS += -I/usr/include/glib-2.0
CPPFLAGS += `pkg-config --libs --cflags gtk+-3.0`
CPPFLAGS += -Wall

LIBS = `pkg-config --libs --cflags gtk+-3.0`


mnemobop: $(objects)
	$(CC) -o $@ $^ $(LIBS)

mnemobop.o: ./src/mnemobop.cpp
	$(CC) -c $^

common.o: ./src/common/common.cpp
	$(CC) -c $^

graphics.o: ./src/graphics/graphics.cpp ./src/graphics/Mnemomenu.ui
	$(CC) -c $^

clean:
	find . -name "*.o" -type f -delete

mrproper:
	rm -f mnemobop
