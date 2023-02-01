CC = g++
CFLAGS = -O3 -Wall -g

all: compile run clean

memcheck: compile check_mem_leak clean

compile: hat.cpp hat.h main.cpp resizable_array.cpp resizable_array.h
	$(CC) $(CFLAGS) -o hat hat.cpp main.cpp resizable_array.cpp 

run: hat
	./hat

check_mem_leak: hat
	# valgrind --tool=memcheck --leak-check=yes hat
	leaks --atExit --groupByType --list -- ./hat 

clean: 
	rm -rf *.o hat hat.dSYM *~
