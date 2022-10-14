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
#include <iomanip>

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

void dfs(int index, int k) {
    if (k == m) {
        for (int i = 1; i <= n; ++i) {
            if (st[i]) cout << setw(3) << i;
        }
        cout << endl;
        return;
    }
    for (int i = index; i <= n; ++i) {
        st[i] = true;
        dfs(i + 1, k + 1);
        st[i] = false;
    }
}

int main() {
    fhj();
    cin >> n >> m;
    memset(st, false, sizeof st);
    dfs(1, 0);
    return 0;
}