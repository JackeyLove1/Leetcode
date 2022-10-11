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


constexpr int N = 100100, M = 250010, INF = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int d[N], pre[N], incf[N];
bool st[N];

inline void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa() {
    memset(st, 0, sizeof st);
    memset(incf, 0, sizeof incf);
    memset(d, 0x3f, sizeof d);
    queue<int> q;
    q.push(S), d[S] = 0, incf[S] = INF;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            auto ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                incf[ver] = std::min(incf[t], f[i]);
                pre[ver] = i;
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
        auto t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}

int nums[N];

int main() {
    fhj();
    memset(h, -1, sizeof h);
    cin >> n;
    S = 0, T = 2 * n + 1;
    for (int i = 1; i <= n; ++i) {
        add(S, i, 1, 0);
        add(i + n, T, 1, 0);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x;
            cin >> x;
            add(i, j + n, INF, x);
        }
    }
    int flow, cost;
    EK(flow, cost);
    cout << cost << endl;
    for (int i = 0; i < idx; i += 2) {
        f[i] += f[i ^ 1], f[i ^ 1] = 0;
        w[i] = -w[i], w[i ^ 1] = -w[i];
    }
    EK(flow, cost);
    cout << -cost << endl;
    return 0;
}