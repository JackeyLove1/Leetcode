#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
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
constexpr int N = 5100, M = 20010, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int d[N], pre[N], incf[N];
bool st[N];

inline void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

inline bool spfa() {
    queue<int> q;
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q.push(S), d[S] = 0, incf[S] = INF;
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q.push(ver);
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

inline void EK(int &flow, int &cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}


inline int get(int x, int y) {
    return x * (m + 1) + y;
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    int a, b;
    cin >> a >> b;
    cin >> n >> m;
    int c;
    S = (n + 1) * (m + 1) + 1, T = S + 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c;
            add(get(i, j), get(i, j + 1), 1, -c);
            add(get(i, j), get(i, j + 1), INF, 0);
        }
    }
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c;
            add(get(j, i), get(j + 1, i), 1, -c);
            add(get(j, i), get(j + 1, i), INF, 0);
        }
    }
    int k, x, y;
    for (int i = 0; i < a; ++i) {
        cin >> k >> x >> y;
        add(S, get(x, y), k, 0);

    }
    for (int i = 0; i < b; ++i) {
        cin >> k >> x >> y;
        add(get(x, y), T, k, 0);
    }
    int flow, cost;
    EK(flow, cost);
    cout << -cost << endl;
    return 0;
}