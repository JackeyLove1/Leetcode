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

constexpr int N = 1050, M = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], cnt[M], dist[N], level[N], idx;
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int s, int low, int high) {
    priority_queue<PII, vector<PII>, greater<>> q;
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (st[u]) continue;
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (level[v] < low || level[v] > high) continue;
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
    }
    return dist[1];
}

int main() {
    fhj();
    memset(h, -1, sizeof h), idx = 0;
    cin >> m >> n;
    int S = 0;
    for (int i = 1; i <= n; i++) {
        int P, L, X;
        cin >> P >> L >> X;
        add(S, i, P);
        level[i] = L;
        for (int j = 0; j < X; ++j) {
            int T, V;
            cin >> T >> V;
            add(T, i, V);
        }
    }
    int res = 10000;
    for (int low = 1; low + m <= 100; ++low) {
        res = std::min(res, dijkstra(S, low, low + m));
    }
    cout << res << endl;
    return 0;
}