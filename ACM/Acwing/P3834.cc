#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            sgn *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * sgn;
}

constexpr int N = 1e5 + 100;
struct Node {
    int l, r, v;
};
std::array<Node, N << 5> tr{};
std::array<int, N> root{}, A{};
int idx{0};
int n, m;
vector<int> nums;

inline int find(int x) {
    return std::lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

inline void pushup(int u) {
    // todo
    auto &root = tr[u], &left = tr[tr[u].l], &right = tr[tr[u].r];
    root.v = left.v + right.v;
}

int build(int l, int r) {
    int p = ++idx;
    if (l == r) {
        return p;
    }
    int mid = l + r >> 1;
    tr[p].l = build(l, mid);
    tr[p].r = build(mid + 1, r);
    pushup(p);
    return p;
}

void pushdown() {
    // todo
}

int insert(int p, int l, int r, int k) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        ++tr[q].v;
        return q;
    }
    int mid = l + r >> 1;
    if (k <= mid) tr[q].l = insert(tr[p].l, l, mid, k);
    else tr[q].r = insert(tr[p].r, mid + 1, r, k);
    pushup(q);
    return q;
}

int update(int p, int l, int r, int x, int k) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[q].v = k;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = update(tr[p].l, l, mid, x, k);
    else tr[q].r = update(tr[p].r, mid + 1, r, x, k);
    pushup(q);
    return q;
}

int query(int p, int l, int r, int k) {
    if (l == r) return r;
    int mid = l + r >> 1, cnt = tr[p].v;
    if (k <= mid) return query(tr[p].l, l, mid, k);
    else return query(tr[p].r, mid + 1, r, k - cnt);
}

int query(int p, int q, int l, int r, int k) {
    if (l == r) return r;
    int cnt = tr[tr[p].l].v - tr[tr[q].l].v;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[p].l, tr[q].l, l, mid, k);
    else return query(tr[p].r, tr[q].r, mid + 1, r, k - cnt);
}

int main() {
    n = read(), m = read();
    nums.reserve(n);
    for (int i = 1; i <= n; ++i) {
        A[i] = read();
        nums.push_back(A[i]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    root[0] = build(1, n);
    for (int i = 1; i <= n; ++i) {
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(A[i]));
    }
    while (m--) {
        int l, r, k;
        l = read(), r = read(), k = read();
        printf("%d\n", nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)]);
    }
    return 0;
}