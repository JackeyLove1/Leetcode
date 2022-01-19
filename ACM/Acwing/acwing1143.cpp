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

constexpr int N = 2200;

int p[N];
int n, m;

struct Edge {
    int a, b, w;

    bool operator<(const Edge &W) const {
        return w < W.w;
    }
};

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    vector<Edge> edges;
    edges.reserve(m);
    int res = 0;
    for (int i = 0; i < m; ++i) {
        int ps, a, b, w;
        cin >> ps >> a >> b >> w;
        if (ps == 1) {
            res += w;
            int pa = find(a), pb = find(b);
            p[pa] = pb;
        } else {
            edges.push_back({a, b, w});
        }
    }
    sort(edges.begin(), edges.end());
    for (const auto &edge : edges) {
        int pa = find(edge.a), pb = find(edge.b), w = edge.w;
        if (pa != pb) {
            p[pa] = pb;
            res += w;
        }
    }
    cout << res << endl;
    return 0;
}