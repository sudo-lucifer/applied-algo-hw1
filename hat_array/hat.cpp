#include <array>
#include <cstddef>
#include <iostream>
#include "hat.h"

using namespace std;

HatArray::HatArray(int b) {
        array_pointer = (int**) malloc(sizeof(int) * b);
        for (int i = 0; i < b; i++) {
                array_pointer[i] = (int*) malloc(sizeof(int) * b);
        }
        array_pointer[0][0] = 10;

        b_size = b;
        total_keys = 0;
}

void HatArray::push(int element) {
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

