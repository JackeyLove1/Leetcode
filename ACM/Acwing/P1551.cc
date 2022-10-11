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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

using namespace std;

constexpr int N = 50100, M = 20010, INF = 1e8;
int p[N], w[N];

int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return x;
}

inline void merge(int a, int b) {
    auto pa = find(a), pb = find(b);
    if (pa != pb) {
        p[pb] = pa;
    }
}

int main() {
    fhj();
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    int a, b;
    while (m--) {
        cin >> a >> b;
        merge(a, b);
    }
    while (k--) {
        cin >> a >> b;
        auto pa = find(a), pb = find(b);
        if (pa != pb) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}