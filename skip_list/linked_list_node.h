#include <iostream>

#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

using namespace std;
class LinkedListNode{
        public:
		int key;
		LinkedListNode *right_node;

                LinkedListNode(int new_key) {
			key = new_key;
		}
                void change_key(int new_key) {
			key = new_key;
		}
		void change_linked_node(LinkedListNode *new_node) {
			right_node = new_node;
		}
                int get_key() {
			return key;
		}

                string toString() {
			return "Node " + to_string(key);
		}
};

#endif
