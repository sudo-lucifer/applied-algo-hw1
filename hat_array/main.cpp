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
        long total = 0;
        for (int i = 0; i < n; i++) {
                total += hat_push_one(i);
        }
        return total;
}

long resizable_push_one(int i) {
        ResizableArray resizable_array;
        long begin = rdtsc();
        resizable_array.push(i);
        long end = rdtsc();
        resizable_array.destroy();
        return end - begin;
}

long resizable_push_n(int n) {
        long total = 0;
        for (int i = 0; i < n; i++) {
                total += resizable_push_one(i);
        }
        return total;
}

long benchmark_hat_push_n(int round, int push_amount) {
        long total = 0;
        for (int i = 0; i < round; i++) {
                total += hat_push_n(push_amount);
        }
        return total / round;

}

long benchmark_resizable_array_push_n(int round, int push_amount) {
        long total = 0;
        for (int i = 0; i < round; i++) {
                total += resizable_push_n(push_amount);
        }
        return total / round;

}

// void save_push_benchmark(int push_amount) {
//         cout << "Start recording benchmark data\n";
//         ofstream HatFile("hat_benchmark.csv");
//         ofstream ResizableArrayFile("resizable_array_benchmark.csv");
//         ResizableArray resizable_array;
//         HatArray hat_array;
//         HatFile << "size,cpu_count\n";
//         ResizableArrayFile << "size,cpu_count\n";
//         for (int i = 1; i <= push_amount; i++) {
//                 long begin = rdtsc();
//                 hat_array.push(1);
//                 long end = rdtsc();
//                 HatFile << i << "," << (end - begin) << "\n";
//         }
//         HatFile.close();
//         for (int i = 1; i <= push_amount; i++) {
//                 long begin = rdtsc();
//                 resizable_array.push(1);
//                 long end = rdtsc();
//                 ResizableArrayFile << i << "," << (end - begin) << "\n";
//         }
//         ResizableArrayFile.close();
//         hat_array.destroy();
//         resizable_array.destroy();
// }
 


int main() {
        int max_operation = 50;
        int round = 10000;

        ofstream HatFile("hat_benchmark.csv");
        ofstream ResizableArrayFile("resizable_array_benchmark.csv");
        HatFile << "operation_amount,cpu_count\n";
        ResizableArrayFile << "operation_amount,cpu_count\n";
        long total_hat = 0;
        long total_resizable = 0;
        cout << "================== Benchmark ==================\n";
        for (int operation = 1; operation <= max_operation; operation++) {
                long result_hat = benchmark_hat_push_n(round, operation);
                long result_resizable = benchmark_resizable_array_push_n(round, operation);
                total_hat += result_hat;
                total_resizable += result_resizable;
                HatFile << operation << "," << result_hat << "\n";
                ResizableArrayFile << operation << "," << result_resizable << "\n";
        }
        cout << "Overall pushing benchmark from 1 to " << max_operation << " operation\n" ;
        cout << "HAT CPU count: " << (total_hat / max_operation ) << "\n";
        cout << "Resizable array CPU count: " << (total_resizable / max_operation ) << "\n";
        return 0;
}
