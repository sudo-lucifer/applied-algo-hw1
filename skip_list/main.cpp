#include <iostream>
#include "./linked_list/linked_list.h"

using namespace std;

int main() {
	LinkedList a;
	// a.push(1);
	// a.push(2);
	// a.push(3);
	cout << a.toString() << "\n";
	a.destroy();
	return 0;
}