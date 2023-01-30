#include <iostream>
#include "hat.h"

using namespace std;


int main() {
        HatArray a(2);
        cout << a.toString();
        a.destroy();
        return 0;
}
