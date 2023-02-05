CC = g++
CFLAGS = -O3 -Wall -g

all: compile run clean

memcheck: compile check_mem_leak clean

compile: linked_list_node.h linked_list.cpp linked_list.h
	$(CC) $(CFLAGS) -o linked_list.o main.cpp linked_list.cpp 

run: linked_list.o
	./linked_list.o

check_mem_leak: 
	leaks --atExit --groupByType --list -- ./linked_list.o 

clean: 
	rm -rf *.o linked_list.o.dSYM *~
