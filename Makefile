sources=mnemobop.cpp
sources+=common.cpp
headers=common.h
objects=$(sources:.cpp=.o)

mnemobop: mnemobop.o common.o
	g++ -o $@ $^

mnemobop.o: mnemobop.cpp
	g++ -Wall -c $^

common.o: common.cpp
	g++ -Wall -c $^

clean:
	rm -f *.o

mrproper:
	rm -f Mnemobop
