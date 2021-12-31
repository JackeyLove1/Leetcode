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
namespace graph {
    int h[N], e[N], ne[N], w[N], idx;
    int n;
    int dist[N];
    bool st[N];
    constexpr int INF = 0x3f3f3f3f;

    int dijkstra() {
        memset(dist, 0x3f, sizeof dist);
        using PII = pair<int, int>;
        priority_queue<PII, vector<PII>, greater<>> heap;
        heap.push({0, 1}); // dist, ver
        st[1] = true;
        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            int dis = t.first, ver = t.second;
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
        return dist[n] >= INF / 2 ? -1 : dist[n];
    }

    int g[N][N];

    void floyed() {

    }
}

namespace segmenttree {
    struct Node {
        int l, r;
        int v;
    } tr[N * 4];

    int nums[N];

    inline void pushup(int u) {
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r};
        if (l == r) {
            tr[u].v = nums[l];
            return;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void modify(int u, int x, int v) {
        if (tr[u].l == x && tr[u].r == x) {
            tr[u].v = v;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }

    int query(int u, int l, int r) {
        if (tr[u].l <= l && tr[u].r >= r) {
            return tr[u].v;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        int v = 0;
        if (l <= mid) v = query(u << 1, l, r);
        if (r > mid) v = max(v, query(u << 1 | 1, l, r));
        return v;
    }
}

namespace lazy_segment_tree {
    using ll = long long;
    int nums[N];
    struct Node {
        int l, r;
        ll add, sum;
    } tr[N * 4];

    inline void pushup(int u) {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void pushdown(int u) {
        auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
        if (root.add) {
            left.add += root.add, left.sum += (ll) (left.r - left.l + 1) * root.add;
            right.add += root.add, right.sum += (ll) (right.r - right.l + 1) * right.add;
            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r};
        if (l == r) {
            tr[u].add = 0;
            tr[u].sum = nums[l];
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
        ll v = 0;
        if (l <= mid) v += query(u << 1, l, r);
        if (r > mid) v += query(u << 1 | 1, l, r);
        return v;
    }

}


namespace tree_array {
    int n;
    int tree[N];
    int nums[N];

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int k) {
        for (int i = x; i <= n; i += lowbit(i)) {
            tree[i] += k;
        }
    }

    inline int query(int x) {
        int sum = 0;
        for (int i = x; i; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

    inline void init() {
        for (int i = 1; i <= n; ++i) {
            tree[i] += nums[i];
            int j = i + lowbit(i);
            if (j <= n) tree[j] += tree[i];
        }
    }
}

namespace prefix_tree {
    int son[N][26], cnt[N], idx;

    void insert(const string &str) {
        int p = 0;
        for(const char i : str){
            int u = i - 'a';
            if (!son[p][u]) son[p][u] = ++idx;
            p = son[p][u];
        }
        ++cnt[p];
    }

    int query(const string& str){
        int p = 0;
        for(const char ch : str){
            int u = ch - 'a';
            if (!son[p][u]) return 0;
            p = son[p][u];
        }
        return cnt[p];
    }
}

