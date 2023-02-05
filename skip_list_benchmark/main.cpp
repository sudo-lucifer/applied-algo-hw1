#include <iostream>
#include "./linked_list/linked_list.h"
#include "math.h"
#include "./skip_list/skip_list.h"

using namespace std;

void test_skip_list() {
	// SkipListNode b(1,2);
	int n = 100;
	int max_level_skip_list = log(n);
	SkipList a = SkipList(max_level_skip_list,(float) 1/4);
	for (int i = 1; i <= n; i++) {
		a.insert(i);
	}
	cout << a.toString();
}

void test_linked_list() {
	LinkedList a;
	// SkipListNode b(1,2);
	a.push(1);
	a.push(10);
	a.push(5);
	cout << a.get(0) << "\n";
	cout << a.get(1) << "\n";
	cout << a.get(2) << "\n";
	cout << a.get(3) << "\n";

	cout << a.search(5) << "\n";
	cout << a.toString() << "\n";
	a.destroy();

}

int main() {
	test_skip_list();
	return 0;
}