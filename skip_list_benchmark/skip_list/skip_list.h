#include <iostream>
#include "skip_list_node.h"


#ifndef SKIPLIST_H
#define SKIPLIST_H
using namespace std;

class SkipList {
	public:
		SkipList(int max_level, float p);
		int random_level();
		void insert(int element);
		string toString();
	private:
		float prob;
		SkipListNode* sentinels;
		int current_level;
		int max_list_level;
};
#endif