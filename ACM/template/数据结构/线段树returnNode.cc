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
using PII = pair<int, int>;

constexpr int N = 500000 + 10;
int n, m, p;

struct Node {
    int l, r, d;
    friend ostream& operator << (ostream& os, const Node& node) {
        os << "l: " << node.l <<" r: " << node.r <<" d: " <<node.d << endl;
        return os;
    }
} tr[N * 4];

int w[N];
static unordered_map<int, ull> cnt;

inline ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void pushup(Node &root, Node &left, Node &right) {
    root.d = gcd(left.d, right.d);
    ++cnt[root.d];
}

void pushup(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    pushup(root, left, right);
}


void pushdown(int u) {
    // todo
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l]};
        ++cnt[w[l]];
        // cout << tr[u];
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
        // cout << tr[u];
    }
}


Node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        if (l > mid) return query(u << 1 | 1, l, r);
        auto left = query(u << 1, l, r);
        auto right = query(u << 1 | 1, l, r);
        Node res;
        pushup(res, left, right);
        return res;
    }
}

void modify(int u, int x, int d) {
    if (tr[u].l == x && tr[u].r == x) {
        // todo
    } else {
        // todo
    }
}

int main() {
    fhj();
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cnt.clear();
        memset(w, 0, sizeof w);
        cout << "Case #" << t << ":" << endl;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> w[i];
        build(1, 1, n);
        int l, r;
        cin >> m;
        while (m--) {
            cin >> l >> r;
            auto node = query(1, l, r);
            cout << node.d << " " << cnt[node.d] << endl;
        }
    }
    return 0;
}