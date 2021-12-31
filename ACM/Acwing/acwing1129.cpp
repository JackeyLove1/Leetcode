#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1e6 + 100;

int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];

inline void init() {
    memset(dist, 0x3f, sizeof dist);
    memset(h, -1, sizeof h);
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline int dijkstra(int start, int end) {
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> heap;
    dist[start] = 0;
    heap.push({0, start}); // distance, point
    while (!heap.empty()) {
        auto[distance, point] = heap.top();
        heap.pop();
        if (st[point]) continue;
        st[point] = true;
        for (int i = h[point]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distance + w[i]) {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    return dist[end];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    while (m--) {
        int a, b, d;
        cin >> a >> b >> d;
        add(a, b, d);
        add(b, a, d);
    }
    int res = dijkstra(s, t);
    cout << res << endl;
    return 0;
}