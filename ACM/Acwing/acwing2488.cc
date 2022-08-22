#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

int n, m;
constexpr int N = 50010, M = N * 4, INF = 1e9;
int w[N];
struct Node {
    int l, r;
    multiset<int> s;
} tr[M];

void build(int u, int l, int r) {
    tr[u] = {l, r};
    tr[u].s.insert(-INF), tr[u].s.insert(INF);
    for (int i = l; i <= r; ++i) tr[u].s.insert(w[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void change(int u, int p, int x) {
    tr[u].s.erase(tr[u].s.find(w[p]));
    tr[u].s.insert(x);
    if (tr[u].l == tr[u].r) return;
    int mid = tr[u].l + tr[u].r >> 1;
    if (p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}

int query(int u, int a, int b, int x) {
    if (tr[u].l >= a && tr[u].r <= b) {
        auto it = tr[u].s.lower_bound(x);
        --it;
        return *it;
    }
    int mid = tr[u].l + tr[u].r >> 1, res = -INF;
    if (a <= mid) res = max(res, query(u << 1, a, b, x));
    if (b > mid) res = max(res, query(u << 1 | 1, a, b, x));
    return res;
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    build(1, 1, n);
    while (m--) {
        int op, pos, l, r, x;
        cin >> op;
        if (op == 1) {
            cin >> pos >> x;
            change(1, pos, x);
            w[pos] = x;
        } else {
            cin >> l >> r >> x;
            cout << query(1, l, r, x) << endl;
        }
    }
    return 0;
}