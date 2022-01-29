#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int f[60];

int main() {
    fhj();
    int n;
    f[1] = 1, f[2] = 2, f[3] = 3;
    for (int i = 4; i <= 55; ++i) {
        f[i] = f[i - 1] + f[i - 3];
    }
    while (cin >> n && n != 0) {
        cout << f[n] << endl;
    }
    return 0;
}