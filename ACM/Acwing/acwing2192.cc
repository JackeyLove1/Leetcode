#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
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
constexpr int N = 200, M = 100010, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa() {
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

void EK(int &flow, int &cost) {
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

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    S = 0, T = n + m + 1;
    int a, b, c;
    for (int i = 1; i <= m; ++i) {
        cin >> a;
        add(S, i, a, 0);
    }
    for (int i = m + 1; i <= n + m; ++i) {
        cin >> b;
        add(i, T, b, 0);
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = m + 1; j <= n + m; ++j) {
            cin >> c;
            add(i, j, INF, c);
        }
    }
    int flow, cost;
    EK(flow, cost);
    cout << cost << endl;
    // reverse
    for (int i = 0; i < idx; i += 2) {
        f[i] += f[i ^ 1], f[i ^ 1] = 0;
        w[i] = -w[i], w[i ^ 1] = -w[i ^ 1];
    }
    EK(flow, cost);
    cout << -cost << endl;
    return 0;
}