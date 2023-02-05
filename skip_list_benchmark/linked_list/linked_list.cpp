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
	if (sentinel->right_node != NULL) {
		LinkedListNode *removed_node = sentinel->right_node;
		sentinel->right_node = removed_node->right_node;
		delete removed_node;
		size--;
	}
}

LinkedListNode* LinkedList::get(int index) {
	LinkedListNode* current_node = sentinel->right_node;
	int current_index = 0;
	while (index >= 0 && current_index < index) {
		if (current_node == NULL) {
			break;
		}
		current_node = current_node->right_node;
		current_index++;
	}
	return current_node;
}

LinkedListNode* LinkedList::search(int key) {
	LinkedListNode* current_node = sentinel->right_node;
	while (current_node != NULL) {
		if (current_node->key > key) {
			return NULL;
		}
		else if (current_node->key == key) {
			break;
		}
		current_node = current_node->right_node;
	}
	return current_node;
}

int LinkedList::length() {
	return size;
}

string LinkedList::toString() {
	LinkedListNode *current_node = sentinel->right_node;
	if (current_node == NULL) {
		return "No key";
	}
	while (current_node != NULL) {
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

