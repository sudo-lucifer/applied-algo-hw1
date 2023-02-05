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
			right_node = NULL;
		}
};

#endif
