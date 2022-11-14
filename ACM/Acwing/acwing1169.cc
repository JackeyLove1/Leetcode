// practice 2022-11-12
// author: fanhj
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 100010, M = 300010;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
using ll = long long;
ll dist[N];
int cnt[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int q[N];
int tt = 1, hh = 0;

bool spfa() {
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    st[0] = true;
    q[0] = 0;
    while (tt != hh) {
        auto t = q[--tt];
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return false;
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                }
            }
        }
    }
    return true;
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> c >> a >> b;
        if (c == 1) {
            add(a, b, 0);
            add(b, a, 0);
        } else if (c == 2) {
            add(a, b, 1);
        } else if (c == 3) {
            add(b, a, 0);
        } else if (c == 4) {
            add(b, a, 1);
        } else {
            add(a, b, 0);
        }
    }
    for (int i = 1; i <= n; ++i) {
        add(0, i, 1);
    }
    if (!spfa()) {
        cout << -1 << endl;
    } else {
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            res += dist[i];
        }
        cout << res << endl;
    }
    return 0;
}