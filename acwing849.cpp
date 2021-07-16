// dijkstra 模版题

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

using PII = pair<int, int>;
int n, m;
int h[N], w[N], e[N], ne[N], idx;
int dist[N];
bool st[N];

void init() {
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);

}

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra() {
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<>> heap;
    // {distance, point}
    heap.push({0, 1});

    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, dis = t.first;
        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
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