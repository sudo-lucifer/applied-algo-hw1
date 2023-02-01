#include <ctime>
#include <iostream>
#include <vector>
#include "hat.h"
#include "resizable_array.h"

using namespace std;

 
static __inline__ unsigned long long rdtsc(void){
    unsigned hi, lo;  
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32   );
}

void benchmark_push_one() {
        cout << "Start benchmarking push one element";
        ResizableArray resizable_array;
        HatArray hat_array;
        long begin = rdtsc();
        resizable_array.push(1);
        long end = rdtsc();
        cout << "Traditional resizable array CPU count: " << (end - begin) << "\n";
        begin = rdtsc();
        hat_array.push(1);
        long end = rdtsc();
        cout << "HAT array CPU count: " << (end - begin) << "\n";
        resizable_array.destroy();
        hat_array.destroy();
}
 


int main() {
        benchmark_push_one();
        return 0;
}
