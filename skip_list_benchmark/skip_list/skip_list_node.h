#ifndef SKIPLISTNODE_H
#define SKIPLISTNODE_H


class SkipListNode {
	public:
		int key;
		SkipListNode** node_pointers;

		SkipListNode(int new_key, int level) {
			key = new_key;
			node_pointers = new SkipListNode*[level + 1];
			memset(node_pointers,0,sizeof(SkipListNode*) * (level + 1));

		}
};
#endif