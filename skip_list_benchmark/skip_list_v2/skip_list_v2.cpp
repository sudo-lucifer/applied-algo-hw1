#include <iostream>
#include "skip_list_v2.h"
#include <cstring>

using namespace std;

SkipListV2::SkipListV2(int max_level, float p) {
	max_list_level = max_level;
	prob = p;
	current_level = 0;
	sentinels = new SkipListV2Node(0, max_list_level);
}

int SkipListV2::random_level() {
	int lvl = 1;
	float random_level_prob = (float) rand()/RAND_MAX;

	while(random_level_prob < prob && lvl < max_list_level) {
		random_level_prob = (float) rand()/RAND_MAX;
		lvl++;
	}
	return lvl;
}

void SkipListV2::insert(int element) {
	SkipListV2Node* current_layer_node = sentinels;

	SkipListV2Node** update_forward_node_level = new SkipListV2Node*[max_list_level + 1];
	memset(update_forward_node_level, 0, sizeof(SkipListV2Node*) * (max_list_level + 1));

	// find the place to insert new node
	for (int i = max_list_level; i >= 0; i--) {
		// SkipListV2Node* previous_layer_node = NULL;
		while(current_layer_node->forward[i] != NULL && current_layer_node->forward[i]->key < element) {
			// previous_layer_node = current_layer_node;
			current_layer_node = current_layer_node->forward[i];
		}
		update_forward_node_level[i] = current_layer_node;
	}

	current_layer_node = current_layer_node->forward[0];

	if (current_layer_node == NULL || current_layer_node->key != element) {
		int random_layer = random_level();

		if (random_layer > current_level) {
			for (int i = current_level + 1; i < random_layer + 1; i++){
				update_forward_node_level[i] = sentinels;
			};
			current_level = random_layer;
		}

		// insert new node
		SkipListV2Node* new_node = new SkipListV2Node(element, random_layer);
		for (int i = 0; i < random_layer; i++) {
			new_node->forward[i] = update_forward_node_level[i]->forward[i];
			new_node->backward[i] = update_forward_node_level[i]->backward[i];
			update_forward_node_level[i]->forward[i] = new_node;
			new_node->backward[i] = update_forward_node_level[i];
		}
	}
}

SkipListV2Node* SkipListV2::pick_key(SkipListV2Node* current_node, int element) {
	SkipListV2Node* min_node = NULL;
	SkipListV2Node* compare_node = current_node;
	for (int i = current_level - 1; i >= 0; i--) {
		// cout << "pass" << current_level << "\n";
		if (compare_node->forward[i] != NULL && compare_node->forward[i]->key < element){
			if (min_node == NULL || min_node->key > compare_node->forward[i]->key) {
				min_node = compare_node->forward[i];
			}
		}
	}
	return min_node;
}

SkipListV2Node* SkipListV2::search(int element) {
	SkipListV2Node* current_node = sentinels;
	SkipListV2Node* start_node = sentinels;
	int start_layer = 0;
	for (int i = 0; i <= current_level; i++) {
		if (current_node->forward[i] != NULL && current_node->forward[i]->key <= element) {
			start_node = current_node->forward[i];
			start_layer = i;
		}
	}
	for (int i = start_layer; i >= 0; i--) {
		while(start_node->forward[i] != NULL && start_node->forward[i]->key <= element) {
			start_node = start_node->forward[i];
		}
	}
	// start_node = start_node->forward[0];
	if (start_node && start_node->key == element) {
		return start_node;
	}
	return NULL;
}

string SkipListV2::toString() {
	string result = "";
	for (int i = 0; i < current_level; i++) {
		result += "Level " + to_string(i) + "\n";
		SkipListV2Node* node = sentinels->forward[i];
		while(node != NULL) {
			result += to_string(node->key) + " ";
			node = node->forward[i];
		}
		result += "\n";
	}
	return result;
}
