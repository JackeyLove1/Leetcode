#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
constexpr int N = 110, MOD = 998244353;
ull n;

int main() {
    fhj();
    cin >> n;
    // if n is a prime return 1
    // else judge
    if (n % 2 == 0) {
        cout << n / 2 << endl;
    } else {
        for (ull j = 3; j * j <= n; ++j) {
            if (n % j == 0) {
                n -= j;
                cout << 1 + n / 2 << endl;
                return 0;
            }
        }
        cout << 1 << endl;
    }
    return 0;
}