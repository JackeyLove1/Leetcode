#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;
using ll = long long;
const int N = 1e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int h[N], w[N], e[N], ne[N], idx, pre[N];
ll dist[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    while (heap.size()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                pre[j] = ver;
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] >= INF / 2) return -1;
    return dist[n];
}

int main() {
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    auto res = dijkstra();
    // cout << res << endl;
    if (res == -1) cout << -1 << endl;
    else {
        vector<int> v;
        for (int i = n; i; i = pre[i]) {
            v.push_back(i);
        }
        reverse(v.begin(), v.end());
        for (auto num: v) {
            cout << num << " ";
        }
    }
    return 0;
}
