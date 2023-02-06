#include <iostream>
#include "./linked_list/linked_list.h"
#include "math.h"
#include <fstream>
#include "./skip_list/skip_list.h"
#include "./skip_list_v2/skip_list_v2.h"

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

void scan_latency(int n) {
	ofstream SkipListFile("skip_list_scan.csv");
	ofstream LinkedListFile("linked_list_scan.csv");
	SkipListFile << "operation,cpu_count\n";
	LinkedListFile << "operation,cpu_count\n";
	int max_level_skip_list = log(n);
	SkipList skip_list(max_level_skip_list, (float) 1/4);
	LinkedList linked_list;
	cout << "================ Search ================\n";
	long total_skip_list = 0;
	long total_linked_list = 0;
	for (int i = 1; i <= n; i++) {
		skip_list.insert(i);
		linked_list.push(i);
	}
	for (int i = 1; i <= n; i++) {
		long start = rdtsc();
		skip_list.search(i);
		long end = rdtsc();
		SkipListFile << i << "," << (end - start) << "\n";
		total_skip_list += (end - start);
	}
	for (int i = 1; i <= n; i++) {
		long start = rdtsc();
		linked_list.search(i);
		long end = rdtsc();
		LinkedListFile << i << "," << (end - start) << "\n";
		total_linked_list += (end - start);
	}
	cout << "Average one search cycle count\n";
	cout << "Skip list: " << (total_skip_list / n) << "\n";
	cout << "linked list: " << (total_linked_list / n) << "\n";
	cout << "\nTotal scan cycle cout cycle count\n";
	cout << "Skip list: " << total_skip_list << "\n";
	cout << "linked list: " << total_linked_list << "\n";
}

void scan_v2_latency(int n) {
	ofstream SkipListFile("skip_list_scan.csv");
	ofstream SkipListV2File("skip_list_v2_scan.csv");
	SkipListFile << "operation,cpu_count\n";
	SkipListV2File << "operation,cpu_count\n";
	int max_level_skip_list = 20;
	SkipList skip_list(max_level_skip_list, (float) 1/4);
	SkipListV2 skip_list_v2(max_level_skip_list, (float) 1/4);
	cout << "================ Search V2 ================\n";
	long total_skip_list = 0;
	long total_skip_list_v2 = 0;
	for (int i = 1; i <= n; i++) {
		skip_list.insert(i);
		skip_list_v2.insert(i);
	}
	for (int i = 1; i <= n; i++) {
		long start = rdtsc();
		skip_list_v2.search(i);
		long end = rdtsc();
		SkipListV2File << i << "," << (end - start) << "\n";
		total_skip_list_v2 += (end - start);
	}
	for (int i = 1; i <= n; i++) {
		long start = rdtsc();
		skip_list.search(i);
		long end = rdtsc();
		SkipListFile << i << "," << (end - start) << "\n";
		total_skip_list += (end - start);
	}
	cout << "Average one search cycle count\n";
	cout << "Skip list: " << (total_skip_list / n) << "\n";
	cout << "Skip list v2: " << (total_skip_list_v2 / n) << "\n";
	cout << "\nTotal scan cycle cout cycle count\n";
	cout << "Skip list: " << total_skip_list << "\n";
	cout << "Skip list v2: " << total_skip_list_v2 << "\n";
}

void test_skip_list() {
	int n = 30;
	int max_level_skip_list = log(n);
	SkipList a = SkipList(max_level_skip_list,(float) 1/2);
	for (int i = 1; i <= n; i++) {
		a.insert(i);
	}
	cout << a.toString();
	cout << a.search(2);
}

void test_linked_list() {
	LinkedList a;
	a.push(1);
	a.push(10);
	a.push(5);
	cout << a.get(0) << "\n";
	cout << a.get(1) << "\n";
	cout << a.get(2) << "\n";
	cout << a.get(3) << "\n";

	cout << a.search(6) << "\n";
	cout << a.toString() << "\n";
	a.destroy();
}

void test_skip_list_v2() {
	int n = 100;
	int max_level_skip_list = 10;
	SkipListV2 a(max_level_skip_list, (float) 1/2);
	for (int i = 1; i <= n; i++) {
		a.insert(i);
	}
	cout << a.toString();
	cout << "\n";
	SkipListV2Node* test = a.search(97);
	cout << test->key << "\n";
}

void best_p_for_search(int n) {
	ofstream SkipListFile("best_p_for_search.csv");
	SkipListFile << "p,cpu_count\n";
	int max_level_skip_list = log2(n);
	SkipList skip_list(max_level_skip_list, (float) 1/4);
	cout << "================ Best p ================\n";
	float p = 0.0;
	while (p <= 1) {
		long total_skip_list = 0;
		SkipList skip_list(max_level_skip_list, (float) p);
		for (int i = 1; i <= n; i++) {
			skip_list.insert(i);
		}
		for (int i = 1; i <= n; i++){
			long start = rdtsc();
			skip_list.search(i);
			long end = rdtsc();
			total_skip_list += (end - start);
		}
		SkipListFile << p << "," << (total_skip_list / n) << "\n";
		cout << "p = " << p << ": avevage search cpu cycle count: " <<  (total_skip_list / n) << "\n";
		p = p + (float)(1/8);
	}
	SkipListFile.close();
}

int main() {
	int n = 100;
	// insert_latency(n);
	// scan_latency(n);
	// test_skip_list_v2();
	// scan_v2_latency(n);
	best_p_for_search(n);
	return 0;
}