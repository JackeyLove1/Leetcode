#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

static inline int cnt_(int x) {
    return __builtin_popcount(x);
}

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 100010, M = 3100010;

int n, m;
int w[N];

struct Node {
    int l, r;
    ll add, sum;
    // explicit Node(int l_, int r_, ll add_, ll sum_) : l(l_), r(r_), add(add_), sum(sum_) {}
} tr[N * 4];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.sum += 1l * (left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += 1l * (right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, 0, w[l]};
    else {
        tr[u] = {l, r, 0, 0};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].add += 1l * d;
        tr[u].sum += 1l * (tr[u].r - tr[u].l + 1) * d;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    ll sum = 0;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) sum += query(u << 1, l, r);
    if (r > mid) sum += query(u << 1 | 1, l, r);
    return sum;

}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    build(1, 1, n);
    string op;
    int l, r, d;
    while (m--) {
        cin >> op >> l >> r;
        if (op == "C") {
            cin >> d;
            modify(1, l, r, d);
        } else printf("%lld\n", query(1, l, r));
    }

    return 0;
}