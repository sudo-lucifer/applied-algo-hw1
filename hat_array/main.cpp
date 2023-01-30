#include <iostream>
#include "hat.h"

using namespace std;


int main() {
        HatArray a(2);
        a.push(-1);
        a.push(-2);
        cout << a.toString() + "\n";
        for (int i = 1; i <= 3; i++){
                a.push(i);
                cout << a.toString() + "\n";
        }
        cout << a.toString();
        a.destroy();
        return 0;
}
