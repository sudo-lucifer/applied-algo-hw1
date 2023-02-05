#include <iostream>
#include "linked_list.h"
#include "linked_list_node.h"

using namespace std;

LinkedList::LinkedList() {
	sentinel = new LinkedListNode(0);
	cout << sentinel->toString() + "\n";
	size = 0;
}

void LinkedList::push(int element) {
	return;
}


void LinkedList::pop() {
	return;
}

// LinkedListNode LinkedList::get(int index) {
// 	return new LinkedListNode(-1);
// }

int LinkedList::search(int key) {
	return 1;
}

int LinkedList::length() {
	return size;
}

string LinkedList::toString() {
	return "";
}

void LinkedList::destroy() {
	LinkedListNode *previous_node = sentinel;
	if (size <= 0) {
		delete previous_node;
	}
	for (int i = 0; i < size; i++) {
		LinkedListNode *current_node = previous_node->right_node;
		delete previous_node;
		previous_node = current_node;
	}
}

