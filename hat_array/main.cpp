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

void append_latency(int round, int max_operation) {
        HatArray hat_array;
        ResizableArray resizable_array;
        ofstream HatFile("hat_benchmark.csv");
        ofstream ResizableArrayFile("resizable_array_benchmark.csv");
        HatFile << "operation_amount,cpu_count\n";
        ResizableArrayFile << "operation_amount,cpu_count\n";

        cout << "================== Append Latency  ==================\n";
        long result_resizable = benchmark_resizable_array_push_n(round,1);
        long result_hat = benchmark_hat_push_n(round, 1);
        cout << "HAT CPU count: " << result_hat << "\n";
        cout << "Resizable array CPU count: " << result_resizable << "\n\n";

        for (int operation = 1; operation <= max_operation; operation++) {
                long begin = rdtsc();
                resizable_array.push(operation);
                long end = rdtsc();
                ResizableArrayFile << operation << "," << (end - begin) << "\n";
        }
        for (int operation = 1; operation <= max_operation; operation++) {
                long begin = rdtsc();
                hat_array.push(operation);
                long end = rdtsc();
                HatFile << operation << "," << (end - begin) << "\n";
        }
        hat_array.destroy();
        resizable_array.destroy();
        ResizableArrayFile.close();
        HatFile.close();
}

void access_latency(int round) {
        cout << "================== Access Latency  ==================\n";
        HatArray hat_array;
        ResizableArray resizable_array;
        hat_array.push(1);
        resizable_array.push(1);
        long total_hat = 0;
        long total_resizable = 0;
        for (int i = 0; i < round; i++) {
                long begin = rdtsc();
                hat_array.get(0);
                long end = rdtsc();
                total_hat += (end - begin);
        }
        for (int i = 0; i < round; i++) {
                long begin = rdtsc();
                resizable_array.get(0);
                long end = rdtsc();
                total_resizable += (end - begin);
        }
        cout << "HAT CPU count: " << (total_hat / round) << "\n";
        cout << "Resizable array CPU count: " << (total_resizable / round) << "\n";
        hat_array.destroy();
        resizable_array.destroy();
}


void scan_throughput(int element) {
        cout << "================== Scan Latency  ==================\n";
        HatArray hat_array;
        ResizableArray resizable_array;
        ofstream HatFile("hat_scan_benchmark.csv");
        ofstream ResizableArrayFile("resizable_array_scan_benchmark.csv");
        HatFile << "read,cpu_count\n";
        ResizableArrayFile << "read,cpu_count\n";
        for (int i = 1; i <= element; i++) {
                hat_array.push(i);
                resizable_array.push(i);
        }
        long total_hat = 0;
        long total_resizable = 0;
        for (int i = 0; i < element; i++) {
                long begin = rdtsc();
                hat_array.get(0);
                long end = rdtsc();
                total_hat += (end - begin);
                HatFile << i + 1 << "," << (end - begin) << "\n";
        }
        for (int i = 0; i < element; i++) {
                long begin = rdtsc();
                resizable_array.get(0);
                long end = rdtsc();
                total_resizable += (end - begin);
                ResizableArrayFile << i + 1 << "," << (end - begin) << "\n";
        }
        cout << "HAT CPU count: " << (total_hat) << "\n";
        cout << "Resizable array CPU count: " << (total_resizable) << "\n";
        hat_array.destroy();
        resizable_array.destroy();
}

void overall_throughput(int round, int max_operation) {
        cout << "================== Overall thoughput  ==================\n";
        long total_resizable = benchmark_resizable_array_push_n(round, max_operation);
        long total_hat = benchmark_hat_push_n(round, max_operation);
        cout << "Overall pushing benchmark from 1 to " << max_operation << " operation\n" ;
        cout << "HAT CPU count: " << total_hat << "\n";
        cout << "Resizable array CPU count: " << total_resizable << "\n";
        cout << "========================================================\n";
}

int main() {
        int max_operation = 50;
        int round = 100000;

        append_latency(round, max_operation);
        access_latency(round);
        scan_throughput(max_operation);
        overall_throughput(round, max_operation);
        // HatArray hat_array;
        // int n = 1000;
        // for (int i = 1; i <= n; i++ ) {
        //         hat_array.push(i);
        // }
        // for (int i = 0; i < n; i++) {
        //         if (i + 1 != hat_array.get(i)) {
        //                 cout << "Wrong at index " << i << "\n";
        //         }
        // }
        // cout << hat_array.toString() << "\n";
        // hat_array.destroy();
        return 0;
}
