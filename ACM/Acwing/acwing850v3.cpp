#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

constexpr int N = 1e6 + 100;
int e[N], w[N], ne[N], h[N], idx;
int dist[N];
bool st[N];
int n, m;

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    memset(dist, 0x3f, sizeof dist);
    memset(h, -1, sizeof h);
}

inline int dijkstra() {
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> heap;
    dist[1] = 0;
    heap.push({dist[1], 1}); // dis, ver
    while (!heap.empty()) {
        auto [dis, ver] = heap.top();
        heap.pop();
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            auto j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    cout << dijkstra() << endl;
    return 0;
}