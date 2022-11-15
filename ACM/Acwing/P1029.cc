#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n, m;
    cin >> n >> m;
    int t = n * m;
    int res = 0;
    for (int i = 1; i * i <= t; ++i) {
        if (t % i == 0 && gcd(i, t / i) == n) {
            res += 2;
        }
    }
    if (n == m) --res;
    cout << res << endl;
    return 0;
}