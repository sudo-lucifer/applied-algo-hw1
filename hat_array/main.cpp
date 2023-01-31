#include <iostream>
#include "hat.h"

using namespace std;


int main() {
        HatArray a;
        for (int i = 0; i < 5; i++) {
                a.push(i);
                cout << a.get(i);
                cout << "\n";
        }
        cout << a.toString() + "\n";
        // for (int i = 1; i <= 3; i++){
                // a.push(i);
                // cout << a.toString() + "\n";
        // }
        // cout << a.toString();
        a.destroy();
        return 0;
}
