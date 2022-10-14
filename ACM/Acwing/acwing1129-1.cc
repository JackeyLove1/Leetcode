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

constexpr int N = 1e5 + 100, M = 6200 * 2 + 10, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int S, int T) {
    memset(st, false, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    priority_queue<PII, vector<PII>, greater<>> q; //
    q.push({0, S}); // distance, ver
    while (!q.empty()) {
        auto dis = q.top().first, t = q.top().second;
        q.pop();
        if (st[t]) continue;
        st[t] = true;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                q.push({dist[j], j});
            }
        }
    }
    if (dist[T] == INF) return -1;
    return dist[T];
}

int main() {
    fhj();
    int S, T;
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    cout << dijkstra(S, T) << endl;
    return 0;
}