#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_set>
#include <cmath>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
using PII = pair<int, int>;

static constexpr int N = 2010 + 100, M = 20010 + 100;
ll d1[N], d2[N];
int order[N];

int main() {
    fhj();
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        d1[i] = std::pow(x - x1, 2) + std::pow(y - y1, 2);
        d2[i] = std::pow(x - x2, 2) + std::pow(y - y2, 2);
        order[i] = i;
    }
    sort(order, order + n, [&](int a, int b) {
        return d1[a] == d1[b] ? a > b : d1[a] > d1[b];
    });
    ll res = d1[order[0]], md = 0;
    for (int i = 1; i < n; ++i) {
        md = max(md, d2[order[i - 1]]);
        res = min(res, d1[order[i]] + md);
    }
    res = min(res, max(md, d2[order[n - 1]]));
    cout << res << endl;
    return 0;
}