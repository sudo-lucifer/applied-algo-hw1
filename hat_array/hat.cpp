#include <iostream>
#include "math.h"
#include <stdexcept>
#include <string>
#include "hat.h"

using namespace std;

HatArray::HatArray() {
        b_size = 2;
        total_cap = pow(b_size, 2);
        min_n = pow(b_size / 4, 2);
        array_pointer = (int**) malloc(sizeof(int*) * b_size);
        for (int i = 0; i < b_size; i++) {
                array_pointer[i] = (int*) malloc(sizeof(int) * b_size);
        }
        total_keys = 0;
}

int HatArray::get(int index) {
        if (index >= total_keys || index < 0) {
                destroy();
                throw std::out_of_range("Index out of range");
        }
        int k = 32 - __builtin_clz(b_size) - 1;
        int array_pointer_index = index >> k;
        int block_index = index % b_size;
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
                        while ((n_copy < total_keys) && block_index < new_b_size) {
                                new_array_pointer[pointer_index][block_index] = get(n_copy);
                                block_index++;
                                n_copy++;
                        }
                }
                destroy();
                array_pointer = new_array_pointer;
                b_size = new_b_size;
                total_cap = pow(b_size, 2);
                min_n = pow(b_size / 4,2);
        }
        int k = 32 - __builtin_clz(b_size) - 1;
        int array_pointer_index = total_keys >> k;
        // TODO: change to not use %
        int block_index = total_keys % b_size;
        array_pointer[array_pointer_index][block_index] = element;
        total_keys++;
}

void HatArray::pop() {
        if (total_keys != 0) {
                if (total_keys <= min_n) {
                        int new_b_size = b_size / 2;
                        int** new_array_pointer = (int**) malloc(sizeof(int*) * new_b_size);
                        int n_copy = 0;
                        for (int pointer_index = 0; pointer_index < new_b_size; pointer_index++) {
                                new_array_pointer[pointer_index] = (int*) malloc(sizeof(int) * new_b_size);
                                int block_index = 0;
                                while ((n_copy < total_keys) && block_index < new_b_size) {
                                        new_array_pointer[pointer_index][block_index] = get(n_copy);
                                        block_index++;
                                        n_copy++;
                                }
                        }
                        destroy();
                        array_pointer = new_array_pointer;
                        b_size = new_b_size;
                        total_cap = pow(b_size, 2);
                        min_n = pow(b_size / 4,2);
                }
                total_keys--;
        }
}


int HatArray::length() {
        return total_keys;
}

string HatArray::toString() {
        string result = "[";
        for (int i = 0; i < total_keys; i++) {
                result += to_string(get(i)) + ",";
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

