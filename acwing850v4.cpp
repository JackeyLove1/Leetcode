#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <climits>
#include <queue>

using namespace std;

constexpr int N = 1e6 + 100, INF = 0x3f3f3f3f;
int e[N], w[N], ne[N], h[N], idx;
int dist[N], st[N];
int n, m;

inline void init() {
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline void dijkstra() {
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> heap;
    dist[1] = 0;
    heap.push({0, 1}); // distace, ver
    while (heap.size()) {
        auto[dis, ver] = heap.top();
        heap.pop();
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dis + w[i]) {
                dist[j] = dis + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] >= INF / 2) cout << -1 << endl;
    else cout << dist[n] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    init();
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    dijkstra();
    return 0;
}