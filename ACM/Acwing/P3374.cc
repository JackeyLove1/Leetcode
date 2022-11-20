// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2e6 + 100;
using ll = long long;
ll tr[N], n, m;

inline int lowbit(int x) {
    return x & (-x);
}

inline void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

inline ll query(int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int a[N];

inline void init() {
    for (int i = 1; i <= n; ++i) {
        tr[i] += a[i];
        int j = i + lowbit(i);
        if (j <= n) tr[j] += tr[i];
    }
}

int main() {
    fhj();
    cin >> n >> m;
    int x;
    memset(tr, 0, sizeof tr);
    for (int i = 1; i <= n; ++i) cin >> x, add(i, x);
    while (m--) {
        int id, l, r;
        cin >> id >> l >> r;
        if (id == 1) {
            add(l, r);
        } else {
            cout << query(r) - query(l - 1) << endl;
        }
    }
    return 0;
}