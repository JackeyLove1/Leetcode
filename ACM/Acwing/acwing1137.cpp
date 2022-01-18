#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}


constexpr int N = 1e6 + 100, INF = 0x3f3f3f3f;
int n, m, k;

int e[N], ne[N], h[N], w[N], idx;
int dist[N], st[N];
using PII = pair<int, int>;

inline void init() {
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(w, 0, sizeof w);
    idx = 0;
}

// 无向图
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int source) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
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
            int to = e[i], edge = w[i];
            if (dist[to] > edge + dist[from]) {
                dist[to] = edge + dist[from];
                heap.push({dist[to], to});
            }
        }
    }
}

int main() {
    fhj();
    int s, ws;
    while (cin >> n >> m >> s) {
        init();
        for (int i = 0; i < m; i++) {
            int a, b, t;
            cin >> a >> b >> t;
            add(a, b, t);
        }
        cin >> ws;
        //构造一个虚拟源点0
        for (int i = 0; i < ws; i++) {
            cin >> k;
            add(0, k, 0);
        }
        dijkstra(0);
        int res = dist[s];
        if (res != INF) {
            cout << dist[s] << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}