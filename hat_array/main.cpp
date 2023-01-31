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
        a.destroy();
        return 0;
}
