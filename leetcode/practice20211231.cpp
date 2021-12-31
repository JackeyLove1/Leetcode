#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>
#include <tuple>
#include <climits>

using namespace std;

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

static constexpr int N = 1e3 + 100;
constexpr int INF = 0x3f3f3f3f;
int n;

namespace graph {
    int e[N], w[N], ne[N], h[N], idx;
    int dist[N];
    int d[N];
    bool st[N];
    int g[N][N];

    inline void add(int a, int b, int c) {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    }

    int dijkstra() {
        memset(dist, 0x3f, sizeof dist);
        using PII = pair<int, int>;
        priority_queue<PII, vector<PII>, greater<>> heap;
        heap.push({0, 1}); // distance, ver
        st[1] = true;
        dist[1] = 0;

        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            int ver = t.second;
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

        return dist[n] == INF ? -1 : dist[n];
    }

    void floyed() {
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }

}

namespace lazy_segment_tree {
    using ll = long long;
    struct Node {
        int l, r;
        ll add, sum;
    } tr[N * 4];

    int nums[N];

    void pushup(int u) {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void pushdown(int u) {
        auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
        if (root.add) {
            left.add += root.add, left.sum += (ll) (left.r - left.l + 1) * root.add;
            right.add += root.add, right.sum += (ll) (right.r - right.l + 1) * root.add;
            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r};
        if (l == r) {
            tr[u].sum = nums[l];
            tr[u].add = 0;
            return;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void modify(int u, int l, int r, int d) {
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].sum += (ll) (tr[u].r - tr[u].l + 1) * d;
            tr[u].add += d;
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }

    ll query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) {
            return tr[u].sum;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        ll sum = 0;
        if (l <= mid) sum = query(u << 1, l, r);
        if (r > mid) sum += query(u << 1 | 1, l, r);
        return sum;
    }
}

namespace prefix_tree {
    int son[N][26], cnt[N], idx;

    void insert(const string &str) {
        int p = 0;
        for (const auto ch : str) {
            int u = ch - 'a';
            if (!son[p][u]) son[p][u] = idx++;
            p = son[p][u];
        }
        ++cnt[p];
    }

    int query(const string &str) {
        int p = 0;
        for (const char ch : str) {
            int u = ch - 'a';
            if (!son[p][u]) return 0;
            p = son[p][u];
        }
        return cnt[p];
    }
}

int main() {

}