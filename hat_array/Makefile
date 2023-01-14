CC = g++
CFLAGS = -O3 -Wall -g

all: compile

compile: hat.cpp hat.h main.cpp
	$(CC) $(CFLAGS) -o hat hat.cpp main.cpp

clean: 
	rm -rf *.o hat hat.dSYM *~
