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

constexpr int N = 1e4 + 100, INF = 0x3f3f3f3f;
int n, m;

int e[N], ne[N], h[N], w[N], idx;
int dist[N], st[N];
using PII = pair<int, int>;
unordered_set<int> farms;

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

// 无向图
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int source, int target) {
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
    cin >> m >> n;
    string line;
    vector<int> stop;
    stop.reserve(550);
    init();
    while (m-- >= 0) {
        stop.clear();
        getline(cin, line);
        stringstream ssin(line);
        int p;
        while (ssin >> p) stop.push_back(p);
        for (int i = 0; i < stop.size(); ++i) {
            for (int j = i + 1; j < stop.size(); ++j) {
                if (stop[i] == 1 || stop[j] == 1) {
                    add(stop[i], stop[j], 0);
                    continue;
                }
                add(stop[i], stop[j], 1);
                // add(stop[j], stop[i], 1);
                // cout << "add: " << stop[i] << " " << stop[j] << endl;
            }
        }
    }
    int res = dijkstra(1, n);
    if (res == -1) {
        cout << "NO" << endl;
    } else {
        cout << res << endl;
    }
    return 0;
}