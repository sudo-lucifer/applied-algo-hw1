#include <cstdlib>
#include <iostream>
#include "math.h"
#include <string>
#include "hat.h"

using namespace std;

HatArray::HatArray(int b) {
        array_pointer = (int**) malloc(sizeof(int*) * b);
        for (int i = 0; i < b; i++) {
                array_pointer[i] = (int*) malloc(sizeof(int) * b);
        }
        array_pointer[0][0] = 10;

        b_size = b;
        total_keys = 0;
}

int pow_num(int base, int power) {
        int result = base;
        for (int i = 0; i < power; i++){
                result *= base;
        }
        return base;
}


void HatArray::push(int element) {
        int total_space = pow(b_size, b_size);
        if (total_keys >= total_space) {
                array_pointer = (int**) realloc(array_pointer, sizeof(int*) * (b_size * 2));
                for (int block_index = 0; block_index < b_size * 2; block_index++) {
                        array_pointer[block_index] = (int*) realloc(array_pointer[block_index], sizeof(int) * (b_size * 2));
                }
                // copy data over
                // for (int i = 0; i < total_keys; i++) {
                // }
                b_size *= 2;
                // return;
        }
        int array_pointer_index = floor((total_keys) / b_size);
        int block_index = (total_keys) % b_size;
        int* block_array = array_pointer[array_pointer_index];
        block_array[block_index] = element;
        cout<< "pass end\n";
        total_keys++;
}

void HatArray::pop() {
        total_keys--;
}

int HatArray::get(int index) {
        return 0;
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

