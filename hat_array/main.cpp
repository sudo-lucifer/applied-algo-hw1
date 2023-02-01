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

void benchmark_push_n(int n) {
        cout << "Start benchmarking push n elements\n";
        ResizableArray resizable_array;
        HatArray hat_array;
        long begin = rdtsc();
        for (int i = 0; i < n; i++) {
                resizable_array.push(i);
        }
        long end = rdtsc();
        cout << "Traditional resizable array CPU count: " << (end - begin) << "\n";
        begin = rdtsc();
        for (int i = 0; i < n; i++) {
                hat_array.push(1);
        }
        end = rdtsc();
        cout << "HAT array CPU count: " << (end - begin) << "\n";
        resizable_array.destroy();
        hat_array.destroy();

}

void benchmark_push_one() {
        cout << "Start benchmarking push one element\n";
        ResizableArray resizable_array;
        HatArray hat_array;
        long begin = rdtsc();
        resizable_array.push(1);
        long end = rdtsc();
        cout << "Traditional resizable array CPU count: " << (end - begin) << "\n";
        begin = rdtsc();
        hat_array.push(1);
        end = rdtsc();
        cout << "HAT array CPU count: " << (end - begin) << "\n";
        resizable_array.destroy();
        hat_array.destroy();
}
 


int main() {
        benchmark_push_one();
        cout << "=========================================================\n";
        benchmark_push_n(10);
        return 0;
}
