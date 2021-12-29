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

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

// 约瑟夫环问题（报数移除队列）
int n;

void Joseph_ring() {
    list<int> mylist;
    list<int>::iterator it;
    int k = 2;
    for (int i = 1; i <= n; ++i) mylist.push_back(i);
    while (mylist.size() > 3) {
        int num = 1;
        for (it = mylist.begin(); it != mylist.end();) {
            if (num++ % k) {
                it = mylist.erase(it);
            } else {
                ++it;
            }
        }
        k == 2 ? k = 3 : k = 2;
    }
    for (it = mylist.begin(); it != mylist.end(); ++it) {
        cout << *it << endl;
    }
}

// numbers
static constexpr int N = 1e6 + 10;
namespace graph {
    int e[N], w[N], ne[N], h[N], idx;

    inline void init() {
        memset(h, -1, sizeof h);
        idx = 0;
    }

    inline void add(int a, int b, int c) {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    }

    bool st[N];

    void dfs(int u) {
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (st[j]) continue;
            dfs(j);
        }
    }

    void bfs(int u) {
        queue<int> q;
        q.push(u);
        st[u] = true;
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (st[j]) continue;
                st[j] = true;
                q.push(j);
            }
        }
    }

    int d[N];

    void topsort() {
        queue<int> q;
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (!d[i]) {
                q.push(i);
                ++cnt;
            }
        }
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (--d[j] == 0) {
                    q.push(j);
                    ++cnt;
                }
            }
        }

    }

    int dist[N];

    void dijkstra() {

    }

}

// tree_array

namespace tree_array {
    int tree[N], a[N];

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void init() {
        for (int i = 1; i <= n; ++i) {
            tree[i] += a[i];
            int j = i + lowbit(i);
            if (j <= n) tree[j] += tree[i];
        }
    }

    inline void add(int x, int k) {
        for (int pos = x; pos <= n; pos += lowbit(pos)) {
            tree[pos] += k;
        }
    }

    inline int query(int x) {
        int sum = 0;
        for (int pos = x; pos; pos -= lowbit(x)) {
            sum += tree[pos];
        }
        return sum;
    }
}

// segment_tree
namespace common_segment_tree {
    int nums[N];

    struct Node {
        int l, r;
        int v;
    } tr[N * 4];

    inline void pushup(int u) {
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }

    inline void build(int u, int l, int r) {
        tr[u] = {l, r};
        if (l == r) {
            tr[u].v = nums[l];
            return;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    int query(int u, int l, int r) {
        if (tr[u].l <= l && tr[u].r >= r) {
            return tr[u].v;
        }
        int v = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) v = query(u << 1, l, r);
        if (r > mid) v = max(v, query(u << 1 | 1, l, r));
        return v;
    }

    void modify(int u, int x, int v) {
        if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
        else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x <= mid) modify(u << 1, x, v);
            else modify(u << 1 | 1, x, v);
            pushup(u);
        }
    }
}

namespace lazy_segment_tree {
    using ll = long long;
    struct Node {
        int l, r;
        ll sum, add;
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
        if (l == r) {
            tr[u] = {l, r, nums[l], 0};
            return;
        }
        int mid = l + r >> 1;
        tr[u] = {l, r};
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void modify(int u, int l, int r, int d) {
        if (tr[u].l <= l && tr[u].r <= r) {
            tr[u].sum += (ll) (tr[u].r - tr[u].l + 1) * d;
            tr[u].add += d;
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, mid, d);
        if (r > mid) modify(u << 1 | 1, mid + 1, r, d);
        pushup(u);
    }

    ll query(int u, int l, int r) {
        if (tr[u].l <= l && tr[u].r >= r) return tr[u].sum;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        ll sum = 0;
        if (l <= mid) sum += query(u << 1, l, r);
        if (r > mid) sum += query(u << 1 | 1, l, r);
        return sum;
    }
}