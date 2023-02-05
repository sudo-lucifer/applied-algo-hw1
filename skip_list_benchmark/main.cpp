#include <iostream>
#include "./linked_list/linked_list.h"
#include "math.h"
#include <fstream>
#include "./skip_list/skip_list.h"

using namespace std;

static __inline__ unsigned long long rdtsc(void){
    unsigned hi, lo;  
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32   );
}


void insert_latency(int n) {
	ofstream SkipListFile("skip_list_insert.csv");
	ofstream LinkedListFile("linked_list_insert.csv");
	SkipListFile << "operation,cpu_count\n";
	LinkedListFile << "operation,cpu_count\n";
	int max_level_skip_list = log(n);
	SkipList skip_list(max_level_skip_list, (float) 1/4);
	LinkedList linked_list;
	cout << "================ Insert ================\n";
	long total_skip_list = 0;
	long total_linked_list = 0;
	for (int i = 1; i <= n; i++) {
		long start = rdtsc();
		skip_list.insert(i);
		long end = rdtsc();
		SkipListFile << i << "," << (end - start) << "\n";
		total_skip_list += (end - start);
	}
	for (int i = 1; i <= n; i++) {
		long start = rdtsc();
		linked_list.push(i);
		long end = rdtsc();
		LinkedListFile << i << "," << (end - start) << "\n";
		total_linked_list += (end - start);
	}
	cout << "Average one insertion cycle count\n";
	cout << "Skip list: " << (total_skip_list / n) << "\n";
	cout << "linked list: " << (total_linked_list / n) << "\n";
	cout << "\nTotal cycle cout of " << n << " insertion cycle count\n";
	cout << "Skip list: " << total_skip_list << "\n";
	cout << "linked list: " << total_linked_list << "\n";
}

// void test_skip_list() {
// 	int n = 20;
// 	int max_level_skip_list = log(n);
// 	SkipList a = SkipList(max_level_skip_list,(float) 1/4);
// 	for (int i = 1; i <= n; i++) {
// 		a.insert(i);
// 	}
// 	cout << a.toString();
// 	cout << a.search(21);
// }

// void test_linked_list() {
// 	LinkedList a;
// 	a.push(1);
// 	a.push(10);
// 	a.push(5);
// 	cout << a.get(0) << "\n";
// 	cout << a.get(1) << "\n";
// 	cout << a.get(2) << "\n";
// 	cout << a.get(3) << "\n";

// 	cout << a.search(6) << "\n";
// 	cout << a.toString() << "\n";
// 	a.destroy();
// }

int main() {
	int n = 10000;
	insert_latency(n);
	return 0;
}