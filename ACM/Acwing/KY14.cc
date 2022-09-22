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

constexpr int N = 1e6 + 10, M = 1250, INF = 0x3f3f3f3f;
int a[N], f[N];

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

int n, m;

int main() {
    fhj();
    cin >> m >> n;
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++i) cin >> a[i];
    f[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = m; j >= a[i]; --j) {
            f[j] = std::min(f[j], f[j - a[i]] + 1);
        }
    }
    if (f[m] >= INF) cout << 0 << endl;
    else cout << f[m] << endl;
    return 0;
}