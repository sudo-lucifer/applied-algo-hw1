#include <iostream>
#include "math.h"
#include <stdexcept>
#include <string>
#include "resizable_array.h"

using namespace std;

ResizableArray::ResizableArray() {
        total_cap = 1;
        min_n = 0;
        array = (int*) malloc(sizeof(int) * total_cap);
        size = 0;
}

int ResizableArray::get(int index) {
        if (index >= size || index < 0) {
                destroy();
                throw std::out_of_range("Index out of range");
        }
        return array[index];
}


void ResizableArray::push(int element) {
        if (size >= total_cap) {
		total_cap *= 2;
		int* new_array = (int*) malloc(sizeof(int) * total_cap);
		for (int i = 0; i < size; i++) {
			new_array[i] = array[i];
		}
		destroy();
		array = new_array;
		min_n = total_cap / 4;
        }
	array[size] = element;
        size++;
}

void ResizableArray::pop() {
        if (size != 0) {
                if (size <= min_n) {
			total_cap /= 2;
			int* new_array = (int*) malloc(sizeof(int) * total_cap);
			for (int i = 0; i < size; i++) {
				new_array[i] = array[i];
			}
			destroy();
			array = new_array;
			min_n = total_cap / 4;
                }
                size--;
        }
}


int ResizableArray::length() {
        return size;
}

string ResizableArray::toString() {
        string result = "[";
        for (int i = 0; i < size; i++) {
                result += to_string(get(i));
                if (i != size - 1) {
                        result += ",";
                }
        }
        result += "]";
        return result;
}

void ResizableArray::destroy() {
        free(array);
}

