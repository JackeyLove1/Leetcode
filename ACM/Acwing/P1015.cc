#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

using namespace std;

/*
constexpr int N = 100100, M = 250010, INF = 0x3f3f3f3f;

// cur为当前弧
// d为层次图的层次
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
ll q[N], d[N], cur[N];

// 同EK的add
inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++; // 正向边
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++; // 反向边
}

// 判断是否有增广路，如果有就将其建立出来
// 顺便建立分层图
bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                // ver点没有更新
                // ver的层次+1
                d[ver] = d[t] + 1;
                // 弧优化到当前弧
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

// 搜索从当前点出发，最多可以流的流量
// dfs搜索
ll find(int u, ll limit) {
    if (u == T) return limit;
    ll flow = 0;
    // cur[i]代表当前没有满的路径
    // 已经用过且满的路径不需要再搜索了
    // 增加flow<limit是一个显而易见的限制
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        // 先记录一下当前搜索的弧
        cur[u] = i;  // 当前弧优化
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) //当前点是再上一层图的下一层
        {
            int t = find(ver, min((ll) f[i], limit - flow));
            if (!t) d[ver] = -1; // 搜索失败，表示这个点到终点是没有路径的，赋值-1
            // 更新当前容量网络
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

ll dinic() {
    ll r = 0, flow;
    // 如果有增广路
    // 就把所有能够建立的增广路都建立出来
    // 再把其叠加起来
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}
*/
class person {
public:
    int idx;
    string name;
    int score1, score2;
    char master, west;
    int papers;
    int money;

    explicit person(int idx_, string name_, int s1_, int s2_, char M, char W, int papers_) {
        idx = idx_;
        name = std::move(name_);
        score1 = s1_, score2 = s2_;
        master = M, west = W;
        papers = papers_;
        money = 0;
        if (score1 > 80 && papers > 0) money += 8000;
        if (score1 > 85 && score2 > 80) money += 4000;
        if (score1 > 90) money += 2000;
        if (score1 > 85 && W == 'Y') money += 1000;
        if (score2 > 80 && M == 'Y') money += 850;
    }

    bool operator<(const person &rhs) const {
        return money == rhs.money ? idx > rhs.idx : money < rhs.money;
    }
};

int main() {
    fhj();
    int n;
    cin >> n;
    vector<person> ps;
    ps.reserve(n);
    for (int i = 0; i < n; ++i) {
        string name;
        int s1, s2;
        char M, W;
        int papers;
        cin >> name >> s1 >> s2 >> M >> W >> papers;
        ps.emplace_back(i, name, s1, s2, M, W, papers);
    }
    sort(ps.begin(), ps.end());
    auto sum = 0l;
    for (const auto &p: ps) { sum += p.money; }
    cout << ps.back().name << endl;
    cout << ps.back().money << endl;
    cout << sum << endl;
    return 0;
}