#include <iostream>

#ifndef HATARRAY_H
#define HATARRAY_H

using namespace std;
// template<class T>
class HatArray{
        public:
                HatArray();
                void push(int element);
                void pop();
                int length();
                void print();
                string toString();
        private:
                // TODO: change later
                int* arrayPointer;
                int size;
};

#endif
