#include <iostream>
#include "./linked_list/linked_list.h"

using namespace std;

int main() {
	LinkedList a;
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
	return 0;
}