#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    double n;
    cin >> n;
    double l = -100, r = 100;
    while (r - l > 1e-8) {
        double tmp = (l + r) / 2;
        if (tmp * tmp * tmp > n) r = tmp;
        else l = tmp;
    }
    // cout << l << endl;
    printf("%.6lf\n", l);
    return 0;
}