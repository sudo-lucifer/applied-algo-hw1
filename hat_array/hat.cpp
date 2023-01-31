#include <cstdlib>
#include <iostream>
#include "math.h"
#include <stdexcept>
#include <string>
#include "hat.h"

using namespace std;

HatArray::HatArray() {
        b_size = 2;
        total_cap = pow(b_size, b_size);
        array_pointer = (int**) malloc(sizeof(int*) * b_size);
        for (int i = 0; i < b_size; i++) {
                array_pointer[i] = (int*) malloc(sizeof(int) * b_size);
        }
        total_keys = 0;
}

int HatArray::get(int index) {
        if (index >= total_keys) {
                destroy();
                throw std::out_of_range("Index out of range");
        }
        int k = b_size / 2;
        int array_pointer_index = index >> k;
        int block_index = index & (1 >> (k - 1));
        int* block_array = array_pointer[array_pointer_index];
        return block_array[block_index];
}


void HatArray::push(int element) {
        if (total_keys >= total_cap) {
                int new_b_size = b_size * 2;
                int** new_array_pointer = (int**) malloc(sizeof(int*) * new_b_size);
                int n_copy = 0;
                for (int pointer_index = 0; pointer_index < new_b_size; pointer_index++) {
                        new_array_pointer[pointer_index] = (int*) malloc(sizeof(int) * new_b_size);
                        int block_index = 0;
                        while (n_copy < total_keys) {
                                new_array_pointer[pointer_index][block_index] = get(n_copy);
                                block_index++;
                                n_copy++;
                        }
                }
                destroy();
                array_pointer = new_array_pointer;
                b_size = new_b_size;
                total_cap = pow(b_size, b_size);
        }
        int k = b_size / 2;
        int array_pointer_index = total_keys >> k;
        int block_index = total_keys & (1 >> (k - 1));
        array_pointer[array_pointer_index][block_index] = element;
        total_keys++;
}

void HatArray::pop() {
        total_keys--;
}


int HatArray::length() {
        return total_keys;
}

string HatArray::toString() {
        string result = "[";
        for(int i = 0; i < b_size; i++) {
                for (int j = 0; j < b_size; j++) {
                        result += to_string(array_pointer[i][j]);
                        result += ",";
                }
        }
        result += "]";
        return result;
}

void HatArray::destroy() {
        for (int array_pointer_index = 0; array_pointer_index < b_size; array_pointer_index++) {
                free(array_pointer[array_pointer_index]);
        }
        free(array_pointer);
}

