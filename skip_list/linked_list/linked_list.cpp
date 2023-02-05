#include <iostream>
#include "linked_list.h"
#include "linked_list_node.h"

using namespace std;

LinkedList::LinkedList() {
	sentinel = new LinkedListNode(0);
	size = 0;
}

void LinkedList::push(int element) {
	LinkedListNode *previous_node = sentinel;
	LinkedListNode *current_node = sentinel->right_node;
	bool added = 0;
	while (current_node != NULL) {
		if (element <= current_node->key) {
			LinkedListNode *new_node = new LinkedListNode(element);
			previous_node->right_node = new_node;
			new_node->right_node = current_node;
			added = 1;
			break;
		}
		previous_node = current_node;
		current_node = current_node->right_node;
	}
	if (!added) {
		previous_node->right_node = new LinkedListNode(element);
	}
	size++;
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
	LinkedListNode *current_node = sentinel->right_node;
	if (current_node == NULL) {
		return "No key";
	}
	for (int i = 0; i < size; i++) {
		cout << current_node->key << " ";
		current_node = current_node->right_node;
	}
	return "";
}

void LinkedList::destroy() {
	LinkedListNode *previous_node = sentinel;
	while (previous_node != NULL) {
		LinkedListNode *current_node = previous_node->right_node;
		delete previous_node;
		previous_node = current_node;
	}
	delete previous_node;
}

