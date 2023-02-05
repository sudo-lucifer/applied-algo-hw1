CC = g++
CFLAGS = -O3 -Wall -g

all: compile run clean

memcheck: compile check_mem_leak clean

compile: ./linked_list ./skip_list
	$(CC) $(CFLAGS) -o list.o main.cpp ./linked_list/linked_list.cpp ./skip_list/skip_list.cpp

run: list.o
	./list.o

check_mem_leak: 
	leaks --atExit --groupByType --list -- ./list.o 

clean: 
	rm -rf *.o list.o.dSYM *~
