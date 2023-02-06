#include <iostream>
#include "skip_list_v2_node.h"


#ifndef SKIPLISTV2_H
#define SKIPLISTV2_H
using namespace std;

class SkipListV2 {
	public:
		SkipListV2(int max_level, float p);
		int random_level();
		void insert(int element);
		SkipListV2Node* pick_key(SkipListV2Node* current_node, int element);
		SkipListV2Node* search(int element);
		string toString();
	private:
		float prob;
		SkipListV2Node* sentinels;
		int current_level;
		int max_list_level;
};
#endif