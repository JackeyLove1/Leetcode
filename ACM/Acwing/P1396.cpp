#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 2e4 + 100, INF = 0x3f3f3f3f;
int n, m;

int e[N], ne[N], h[N], w[N], idx;
int dist[N], st[N];
using PII = pair<int, int>;

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

// 无向图
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int source, int target) {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[source] = 0;
    priority_queue <PII, vector<PII>, greater<PII>> heap;
    heap.push({0, source}); // distance, ver
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        int from = t.second;
        if (st[from]) continue;
        st[from] = true;
        for (int i = h[from]; i != -1; i = ne[i]) {
            int to = e[i];
            int dis = max(dist[from], w[i]);
            if (dist[to] > dis) {
                dist[to] = dis;
                heap.push({dist[to], to});
            }
        }
    }
    if (dist[target] == INF) return -1;
    return dist[target];
}

int main() {
    fhj();
    int from, to;
    cin >> n >> m >> from >> to;
    int rs, re, ci;
    init();
    for (int i = 0; i < m; ++i) {
        cin >> rs >> re >> ci;
        add(rs, re, ci);
        add(re, rs, ci);
    }
    int res = dijkstra(from, to);
    cout << res << endl;
    return 0;
}