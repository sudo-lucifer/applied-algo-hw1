#include <iostream>

#ifndef HATARRAY_H
#define HATARRAY_H

using namespace std;
class HatArray{
        public:
                HatArray(int b);
                void push(int element);
                void pop();
                int get(int index);
                int length();
                string toString();
                void destroy();
        private:
                int** array_pointer;
                int b_size;
                int total_keys;
};

#endif
