#define ALIGNMENT 8 // must be a power of 2
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 32; i += 2) {
        cout << ALIGN(i) << endl;
    }
    return 0;
}