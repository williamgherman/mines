CC=clang++
CFLAGS=-Wall -Wextra -Wpedantic -O2 -std=c++11

install: mines
	cp mines /usr/local/bin/mines

mines: mines.o
	$(CC) -o mines mines.o $(CFLAGS)

mines.o: mines.cc
	$(CC) -c mines.cc $(CFLAGS)

clean:
	rm -f *.o
