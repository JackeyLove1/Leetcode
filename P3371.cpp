#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

constexpr int N = 1e6 + 100, M = 1e4 + 100;
const int INF = INT_MAX;

int e[N], ne[N], w[N], h[N], idx;
int dist[M];
bool st[M];
int n, m, s;

inline void init() {
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(w, 0, sizeof w);
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    idx = 0;
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int s) {
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> q;
    dist[s] = 0;
    q.push({0, s}); // distance, ver
    while (!q.empty()) {
        auto t = q.top();
        int dis = t.first, ver = t.second;
        q.pop();
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dis + w[i]) {
                dist[j] = dis + w[i];
                q.push({dist[j], j});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        // if (s == i) continue;
        if (dist[i] >= 0x3f3f3f3f / 2) cout << INF << " ";
        else cout << dist[i] << ' ';
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> s;
    init();
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    dijkstra(s);
    return 0;
}