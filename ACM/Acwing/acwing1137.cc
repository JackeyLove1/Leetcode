#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

constexpr int N = 1e4 + 100, INF = 0x3f3f3f3f;
int n, m;

int e[N], ne[N], h[N], w[N], idx;
int dist[N], st[N];
using PII = pair<int, int>;

// 无向图
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline int dijkstra(int source, int target) {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[source] = 0;
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, source}); // distance, ver
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        int from = t.second;
        if (st[from]) continue;
        st[from] = true;
        for (int i = h[from]; i != -1; i = ne[i]) {
            int to = e[i];
            if (dist[to] > dist[from] + w[i]) {
                dist[to] = dist[from] + w[i];
                heap.push({dist[to], to});
            }
        }
    }
    if (dist[target] == INF) return -1;
    return dist[target];
}

int main() {
    fhj();
    int T;
    while (scanf("%d%d%d", &n, &m, &T) != -1) {
        memset(h, -1, sizeof h);
        idx = 0;
        cin >> n >> m >> T;
        int a, b, c;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> c;
            add(a, b, c);
        }
        int ws, ss;
        cin >> ws;
        for (int i = 0; i < ws; ++i) {
            cin >> ss;
            add(0, ss, 0);
        }
        int res = dijkstra(0, T);
        cout << res << endl;
    }
    return 0;
}
