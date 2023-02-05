#include <cstring>

#ifndef SKIPLISTNODEV2_H
#define SKIPLISTNODEV2_H


class SkipListV2Node {
	public:
		int key;
		SkipListV2Node** forward;
		SkipListV2Node** backward;

		SkipListV2Node(int new_key, int level) {
			key = new_key;
			forward = new SkipListV2Node*[level + 1];
			backward = new SkipListV2Node*[level + 1];
			memset(forward,0,sizeof(SkipListV2Node*) * (level + 1));
			memset(backward,0,sizeof(SkipListV2Node*) * (level + 1));
		}
};
#endif