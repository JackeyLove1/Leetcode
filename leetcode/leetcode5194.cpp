#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
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

constexpr int N = 1e5 + 100, INF = 0x3f3f3f3f;
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

int dijkstra(int source) {
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
    int res = 0;
    for (int target : farms) {
        if (target != source) {
            if (dist[target] == INF) return INF;
            res += dist[target];
        }
    }
    return res;
}


class Solution_1 {
public:
    using PII = pair<int, int>;
    const int INF = 1e7;
    map<PII, int> f;

    int solve(int num, int doubles) {
        PII p = std::make_pair(num, doubles);
        if (f.count(p)) return f[p];
        f[p] = INF;
        if (num == 1) return f[p] = 0;
        if (num % 2 == 0 && doubles > 0) {
            f[p] = min(f[p], solve(num / 2, doubles - 1) + 1);
        }
        f[p] = min(f[p], solve(num - 1, doubles) + 1);
        return f[p];
    }

    int minMoves(int target, int maxDoubles) {
        return solve(target, maxDoubles);
    }
};


int main() {
    Solution s;
    cout << s.minMoves(5, 0) << " res: 4" << endl;
    cout << s.minMoves(19, 2) << " res: 7" << endl;
    cout << s.minMoves(766972377, 92) << " res: ?" << endl;
}