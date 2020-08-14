#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int mySqrt(int x) {
    return (int) pow(x, 0.5);
}

int main() {
    cout << mySqrt(4) << endl;
    cout << mySqrt(8) << endl;
    return 0;
}