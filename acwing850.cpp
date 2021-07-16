#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, m;
int e[N], w[N], ne[N], h[N], idx;
int dist[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);
}

using PII = pair<int, int>;

int dijkstra() {
    priority_queue<PII, vector<PII>, greater<>> heap;
    dist[1] = 0;
    heap.push({dist[1], 1});

    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();

        auto ver = t.second, dis = t.first;
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
    cin >> n >> m;
    init();
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    cout << dijkstra() << endl;
    return 0;
}