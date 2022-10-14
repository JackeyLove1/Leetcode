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

constexpr int N = 1e5 + 100, M = 1e5 + 100;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
ll h[N], e[M], w[M], ne[M], cnt[M], idx;
ll dist[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

ll super[N];

bool spfa(int s) {
    queue<int> q;
    memset(st, false, sizeof st);
    memset(cnt, 0, sizeof cnt);
    memset(super,  0x3f, sizeof super);
    super[s] = 0, st[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        st[u] = false;
        for (int i = h[u]; i!= -1; i = ne[i]) {
            int v = e[i];
            if (super[v] > super[u] + w[i]) {
                super[v] = super[u] + w[i];
                if (!st[v]) {
                    st[v] = true;
                    q.push(v);
                    if (++cnt[v] > n) return false;
                }
            }
        }
    }
    return true;
}

void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<>> q;
    // memset(dist, 0x3f, sizeof dist);
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    memset(st, false, sizeof st);
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (st[u]) continue;
        st[u] = true;
        for (int i = h[u]; i!=-1; i = ne[i]) {
            int v = e[i];
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    idx = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    // set super source is 0
    for (int i = 1; i <= n; i++) {
        add(0, i, 0);
    }
    if (!spfa(0)) { // 存在负环
        cout << -1 << endl;
        return 0;
    }
    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; i != -1; i = ne[i]) {
            w[i] += super[u] - super[e[i]];
        }
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        ll ans = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[j] >= INF/2) {
                ans += j * (1e9);
            } else {
                ans += j * (dist[j] + super[j] - super[i]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}