#include <ctime>
#include <iostream>
#include <vector>
#include "hat.h"

using namespace std;

 
static __inline__ unsigned long long rdtsc(void){
    unsigned hi, lo;  
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32   );
}
 


int main() {
        HatArray hat_array;
        vector<int> vector;
        int n = 10;
        long tick = rdtsc();
        for (int i = 1; i <= n; i++) {
                hat_array.push(i);
        }
        cout << "HAT CPU count: " << (rdtsc() - tick) << "\n";
        tick = rdtsc();
        for (int i = 0; i < 10; i++) {
                vector.push_back(i);
        }
        cout << "Vector CPU count: " << (rdtsc() - tick) << "\n";

        // for (int i = 0; i < n; i++) {
                // if (i + 1 != hat_array.get(i)) {
                        // cout << "Wrong at idx: " << i << "\n";
                // }
        // }

        // for (int i = 1; i <= 300; i++) {
        //         hat_array.pop();
        // }
        // cout << hat_array.toString() + "\n";
        hat_array.destroy();
        return 0;
}
