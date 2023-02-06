#include <iostream>
#include "skip_list.h"
#include <cstring>

using namespace std;

SkipList::SkipList(int max_level, float p) {
	max_list_level = max_level;
	prob = p;
	current_level = 0;
	total_nodes = 0;
	sentinels = new SkipListNode(0, max_list_level);
}

int SkipList::random_level() {
	int lvl = 1;
	float random_level_prob = (float) rand()/RAND_MAX;

	while(random_level_prob < prob && lvl < max_list_level) {
		random_level_prob = (float) rand()/RAND_MAX;
		lvl++;
	}
	return lvl;
}

void SkipList::insert(int element) {
	SkipListNode* current_layer_node = sentinels;

	SkipListNode** update_node_level = new SkipListNode*[max_list_level + 1];
	memset(update_node_level, 0, sizeof(SkipListNode*) * (max_list_level + 1));

	// find the place to insert new node
	for (int i = max_list_level; i >= 0; i--) {
		while(current_layer_node->node_pointers[i] != NULL && current_layer_node->node_pointers[i]->key < element) {
			current_layer_node = current_layer_node->node_pointers[i];
		}
		update_node_level[i] = current_layer_node;
	}

	current_layer_node = current_layer_node->node_pointers[0];

	if (current_layer_node == NULL || current_layer_node->key != element) {
		int random_layer = random_level();
		total_nodes += random_layer;

		if (random_layer > current_level) {
			for (int i = current_level + 1; i < random_layer + 1; i++){
				update_node_level[i] = sentinels;
			};
			current_level = random_layer;
		}

		// insert new node
		SkipListNode* new_node = new SkipListNode(element, random_layer);
		for (int i = 0; i < random_layer; i++) {
			new_node->node_pointers[i] = update_node_level[i]->node_pointers[i];
			update_node_level[i]->node_pointers[i] = new_node;
		}
	}
}

SkipListNode* SkipList::search(int element) {
	SkipListNode* current_node = sentinels;
	for (int i = max_list_level; i >= 0; i--) {
		while(current_node->node_pointers[i] != NULL && current_node->node_pointers[i]->key < element) {
			current_node = current_node->node_pointers[i];
		}
	}
	current_node = current_node->node_pointers[0];
	if (current_node && current_node->key == element) {
		return current_node;
	}
	return NULL;
}

string SkipList::toString() {
	string result = "";
	for (int i = 0; i < current_level; i++) {
		result += "Level " + to_string(i) + "\n";
		SkipListNode* node = sentinels->node_pointers[i];
		while(node != NULL) {
			result += to_string(node->key) + " ";
			node = node->node_pointers[i];
		}
		result += "\n";
	}
	return result;
}
