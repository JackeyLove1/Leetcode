#include <iostream>
#include <vector>

using namespace std;

double myPow(double x, int n) {
    if(n < 0) return myPow(1/x, abs(n));
    if (n == 0) return 1.0;
    if (n == 1) return x;
    if (n % 2 == 0) {
        double tmp = myPow(x, n / 2);
        return tmp * tmp;
    } else {
        double tmp = myPow(x, (n - 1) / 2);
        return x * tmp * tmp;
    }
}