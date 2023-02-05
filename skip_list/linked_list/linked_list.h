#include <iostream>
#include "linked_list_node.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

using namespace std;
class LinkedList{
        public:
                LinkedList();
                void push(int element);
                void pop();
                LinkedListNode* get(int index);
		int search(int key);
                int length();
                string toString();
                void destroy();
        private:
		LinkedListNode *sentinel;
		int size;
};

#endif