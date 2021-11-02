#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

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

constexpr int N = 1e6 + 100;
using ll = long long;
int n, m, w[N];

struct Node {
    int l, r;
    ll sum, add;
} tr[N * 4];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add;
        left.sum += (ll) (left.r - left.l + 1) * root.add;
        right.add += root.add;
        right.sum += (ll) (right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}


void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0};
    } else {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (ll) (tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
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
    else {
        ll sum = 0;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) sum += query(u << 1, l, r);
        if (r > mid) sum += query(u << 1 | 1, l, r);
        return sum;
    }
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        int l, r, d;
        if (op == 1) {
            cin >> l >> r >> d;
            modify(1, l, r, d);
        } else {
            cin >> l >> r;
            cout << query(1, l, r) << endl;
        }
    }
    return 0;
}