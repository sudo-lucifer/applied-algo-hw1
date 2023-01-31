#include <ctime>
#include <iostream>
#include <vector>
#include "hat.h"

using namespace std;

 
// uint64_t rdtsc(){
        // uint64_t val;
        // asm volatile("mrs %0, cntvct_el0" : "=r" (val));
        // return val;
// }

// uint64_t rdtsc(){
//     unsigned int lo,hi;
//     __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
//     return ((uint64_t)hi << 32) | lo;
// }
 


int main() {
        HatArray hat_array;
        vector<int> vector;
        // uint64_t hat_tick = rdtsc();
        hat_array.push(1);
        // cout << "HAT CPU count: " << (rdtsc() - hat_tick) << "\n";
        // uint64_t vector_tick = rdtsc();
        vector.push_back(1);
        // cout << "Vector CPU count: " << (rdtsc() - vector_tick) << "\n";
        // for (int i = 0; i < 5; i++) {
                // hat_array.push(i);
                // vector.push_back(i);
                // cout << hat_array.get(i);
                // cout << "\n";
        // }
        cout << hat_array.toString() + "\n";
        hat_array.destroy();
        return 0;
}
