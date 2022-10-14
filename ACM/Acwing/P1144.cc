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

constexpr int N = 1000005, M = 4000005, MOD = 100003;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], cnt[M], idx, f[N];
ll dist[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<>> q;
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    memset(f, 0, sizeof f);
    dist[s] = 0, f[s] = 1;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (st[u]) continue;
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (dist[v] == dist[u] + w[i]) {
                f[v] = (f[v] + f[u]) % MOD;
            }else if (dist[v] > dist[u] + w[i]) {
                f[v] = f[u];
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    fhj();
    memset(h, -1, sizeof h), idx = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b, 1);
        add(b, a, 1);
    }
    dijkstra(1);
    for (int i = 1; i <= n; ++i){
        cout << f[i] << endl;
    }
    return 0;
}