#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

int n, m, s;
constexpr int N = 1e6 + 100, INF = 0x3f3f3f3f;
int e[N], w[N], ne[N], h[N], idx;
int dist[N], st[N];

inline void init() {
    memset(dist, 0x3f, sizeof dist);
    memset(h, -1, sizeof h);
    idx = 0;
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

using PII = pair<int, int>;

inline void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    dist[s] = 0;
    heap.push({dist[s], s}); // distance, ver
    while (!heap.empty()) {
        auto[dis, ver] = heap.top();
        heap.pop();
        if (st[ver]) continue;
        st[ver] = 1;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        // if (i == s) continue;
        cout << dist[i] << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin >> n >> m >> s;
    int a, b, c;
    while (m--) {
        cin >> a >> b >> c;
        add(a, b, c);
    }
    dijkstra(s);
    return 0;
}