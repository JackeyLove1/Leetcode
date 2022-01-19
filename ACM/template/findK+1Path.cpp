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


constexpr int N = 1e7 + 100, INF = 0x3f3f3f3f;
int n, m, k;

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
            // 取第k+1大的路径
            edge = max(edge, dist[from]);
            if (dist[to] > edge) {
                dist[to] = edge;
                heap.push({dist[to], to});
            }
        }
    }
}

int main() {
    fhj();
    cin >> n >> m >> k;
    int a, b, c;
    init();
    while (m--) {
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
        for (int i = 1; i <= k; ++i) {
            // 添加 i-1层到i层的路径
            add(a + (i - 1) * n, b + i * n, 0);
            add(b + (i - 1) * n, a + i * n, 0);
            // 添加第i层的路径
            add(a + i * n, b + i * n, c);
            add(b + i * n, a + i * n, c);
        }
    }
    for (int i = 1; i <= k; ++i) {
        // 将每层的终点串联，并设置0，标志他们之间等价
        add(i * n, (i + 1) * k, 0);
    }
    dijkstra(1);
    auto res = dist[(k + 1) * n];
    if (res == INF) { cout << "-1" << endl; }
    else { cout << res << endl; }
    return 0;
}