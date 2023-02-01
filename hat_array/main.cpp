#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include "hat.h"
#include "resizable_array.h"

using namespace std;

 
static __inline__ unsigned long long rdtsc(void){
    unsigned hi, lo;  
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32   );
}

long hat_push_one(int i) {
        HatArray hat_array;
        long begin = rdtsc();
        hat_array.push(i);
        long end = rdtsc();
        hat_array.destroy();
        return end - begin;
}

long hat_push_n(int n) {
        HatArray hat_array;
        long total = 0;
        for (int i = 0; i < n; i++) {
                total += hat_push_one(i);
        }
        hat_array.destroy();
        return total;
}

void benchmark_push_n(int round, int push_amount) {
        cout << "Start benchmarking push n elements\n";
        long total = 0;
        for (int i = 0; i < round; i++) {
                total += hat_push_n(push_amount);
        }
        cout << "HAT array CPU count: " << (total / round) << "\n";

}

// void benchmark_push_one() {
//         cout << "Start benchmarking push one element\n";
//         ResizableArray resizable_array;
//         HatArray hat_array;
//         long begin = rdtsc();
//         resizable_array.push(1);
//         long end = rdtsc();
//         cout << "Traditional resizable array CPU count: " << (end - begin) << "\n";
//         resizable_array.destroy();
//         begin = rdtsc();
//         hat_array.push(1);
//         end = rdtsc();
//         cout << "HAT array CPU count: " << (end - begin) << "\n";
//         hat_array.destroy();
// }

void save_push_benchmark(int push_amount) {
        cout << "Start recording benchmark data\n";
        ofstream HatFile("hat_benchmark.csv");
        ofstream ResizableArrayFile("resizable_array_benchmark.csv");
        ResizableArray resizable_array;
        HatArray hat_array;
        HatFile << "size,cpu_count\n";
        ResizableArrayFile << "size,cpu_count\n";
        for (int i = 1; i <= push_amount; i++) {
                long begin = rdtsc();
                hat_array.push(1);
                long end = rdtsc();
                HatFile << i << "," << (end - begin) << "\n";
        }
        HatFile.close();
        for (int i = 1; i <= push_amount; i++) {
                long begin = rdtsc();
                resizable_array.push(1);
                long end = rdtsc();
                ResizableArrayFile << i << "," << (end - begin) << "\n";
        }
        ResizableArrayFile.close();
        hat_array.destroy();
        resizable_array.destroy();
}
 


int main() {
        // benchmark_push_one();
        // cout << "=========================================================\n";
        benchmark_push_n(100,10);
        cout << "=========================================================\n";
        save_push_benchmark(50);
        return 0;
}
