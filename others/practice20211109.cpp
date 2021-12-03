#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e6 + 100;

// simple segment tree
namespace simple_segment_tree {
    using ll = long long;
    int w[N];
    struct Node {
        int l, r;
        int v;
    } tr[N * 4];

    void pushup(int u) {
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            tr[u] = {l, r, w[l]};
        } else {
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) {
            return tr[u].v;
        } else {
            int mid = tr[u].r + tr[u].r >> 1;
            int v;
            if (l <= mid) v = query(u << 1, l, mid);
            if (r > mid) v = max(v, query(u << 1 | 1, mid + 1, r));
            return v;
        }
    }

    void modify(int u, int x, int v) {
        if (tr[u].l == tr[u].r) {
            tr[u].v = v;
        } else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x <= mid) modify(u << 1, x, v);
            if (x > mid) modify(u << 1 | 1, x, v);
            pushup(u);
        }
    }

}

namespace segment_tree {
    int w[N];
    struct Node {
        int l, r;
        int sum, add;
    } tr[N * 4];

    void pushup(int u) {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void pushdown(int u) {
        auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
        if (root.add) {
            left.add += root.add;
            left.sum += (left.r - left.l + 1) * root.add;
            right.add += root.add;
            right.sum += (right.r - right.l + 1) * root.add;
            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        if (l == r) {
            tr[u] = {l, r, w[l], 0};
        } else {
            tr[u] = {l, r};
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    void modify(int u, int l, int r, int d) {
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].sum += (tr[u].r - tr[u].l + 1) * tr[u].add;
            tr[u].add += d;
        } else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if (l <= mid) modify(u << 1, l, mid, d);
            if (r > mid) modify(u << 1 | 1, mid + 1, r, d);
            pushup(u);
        }
    }

    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) {
            return tr[u].sum;
        } else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            int v = 0;
            if (l <= mid) v += query(u << 1, l, mid);
            if (r > mid) v += query(u << 1 | 1, mid + 1, r);
            return v;
        }
    }

}

namespace treeArray {
    int n;
    int a[N], tree[N];

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int k) {
        for (int pos = x; pos <= n; pos += lowbit(pos)) {
            tree[pos] += k;
        }
    }

    inline int query(int x) {
        int res = 0;
        for (int pos = x; pos; pos -= lowbit(pos)) {
            res += tree[pos];
        }
        return res;
    }
}
