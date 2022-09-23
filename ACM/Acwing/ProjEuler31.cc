#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>

using namespace std;

using ll = long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 11100, M = 1250, INF = 0x3f3f3f3f;

int f[N];
constexpr int w[]{1, 2, 5, 10, 20, 50, 100, 200};

int main() {
    fhj();
    memset(f, 0, sizeof f);
    const auto len = sizeof(w) / sizeof(w[0]);
    const auto m = 200;
    f[0] = 1;
    for (int i = 0; i < len; ++i) {
        for (int j = w[i]; j <= m; ++j) {
            f[j] += f[j - w[i]];
        }
    }
    cout << f[m] << endl;
    return 0;
}