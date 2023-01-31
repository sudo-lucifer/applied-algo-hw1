CC = g++
CFLAGS = -O3 -Wall -g

all: compile

compile: hat.cpp hat.h main.cpp
	$(CC) $(CFLAGS) -o hat hat.cpp main.cpp

check_mem_leak: hat
	# valgrind --tool=memcheck --leak-check=yes hat
	leaks --atExit --list -- ./hat 

clean: 
	rm -rf *.o hat hat.dSYM *~
