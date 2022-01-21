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
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

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

static constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f, M = 500;
int e[N], w[N], ne[N], h[N], idx;

inline void init() {
    memset(h, -1, sizeof h);
    // memset ...
    idx = 0;
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

using PII = pair<int, int>;

namespace common {
    int p[N], nums[N]; // parent
    int find(int x) {
        if (x != p[x]) p[x] = find(p[x]);
        return p[x];
    }

    inline void merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            p[pa] = pb;
        }
    }
}
namespace shartest_path {
    bool st[N];
    int dist[N];
    int n, m;

    int dijkstra(int source) {
        memset(dist, 0x3f, sizeof dist);
        memset(st, 0, sizeof st);
        priority_queue<PII, vector<PII>, greater<>> heap;
        heap.push({0, source}); // distance, ver
        dist[source] = 1;
        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            auto ver = t.first;
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
        if (dist[n] == INF) return -1;
        return dist[n];
    }
}

namespace minimum_tree {
    int n, m;

    class edge {
    public:
        int u, v, w;

        explicit edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}

        bool operator<(const edge &rhs) const {
            return w < rhs.w;
        }
    };

    int kruskal() {
        cin >> n >> m;
        vector<edge> edges;
        edges.reserve(m + 10);
        for (int i = 0; i < m; ++i) {
            // add edge
            int a, b, c;
            cin >> a >> b >> c;
            edges.emplace_back(a, b, c);
        }

        sort(edges.begin(), edges.end());

        
    }
}