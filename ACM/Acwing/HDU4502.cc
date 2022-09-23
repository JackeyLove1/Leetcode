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

constexpr int N = 1e6 + 10, M = 1250, INF = 0x3f3f3f3f;

struct work {
    int s, e, w;

    bool operator<(const work &rhs) const {
        return e < rhs.e;
    }
} works[N];

ll f[N];

int n, m;

inline void solve() {
    cin >> m >> n;
    memset(works, 0, sizeof works);
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; ++i) {
        cin >> works[i].s >> works[i].e >> works[i].w;
    }
    sort(works, works + n);
    for (int i = 0; i < n; ++i) {
        auto cost = works[i].e - works[i].s;
        for (int j = m; j >= works[i].e; --j) {
            f[j] = std::max(f[j], f[j - cost] + works[i].w);
        }
    }
    cout << f[m] << endl;
}

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}