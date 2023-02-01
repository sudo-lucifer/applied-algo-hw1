#include <iostream>

#ifndef RESIZABLE_ARRAY_H
#define RESIZABLE_ARRAY_H

using namespace std;
class ResizableArray{
        public:
                ResizableArray();
                void push(int element);
                void pop();
                int get(int index);
                int length();
                string toString();
                void destroy();
        private:
                int* array;
                int size;
                int total_cap;
                int min_n;
};

#endif
