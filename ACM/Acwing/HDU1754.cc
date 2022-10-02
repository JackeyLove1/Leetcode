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

constexpr int N = 200000 + 100;
int n, m, p;

struct Node {
    int l, r;
    ll v;

    friend ostream &operator<<(ostream &os, const Node &node) {
        os << "l: " << node.l << " r: " << node.r << " v: " << node.v;
        return os;
    }
} tr[N * 4];

int w[N];


void pushup(Node &root, Node &left, Node &right) {
    root.v = std::max(left.v, right.v);
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
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
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
        Node res = {l, r, 0};
        pushup(res, left, right);
        return res;
    }
}

void modify(int u, int x, int d) {
    if (tr[u].l == x && tr[u].r == x) {
        tr[u].v = d;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, d);
        else modify(u << 1 | 1, x, d);
        pushup(u);
    }
}

void print(){
    for (int u = 1; u <= n; ++u){
        cout << tr[u] << endl;
    }
    cout << endl;
}
int main() {
    fhj();
    memset(w, 0, sizeof w);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    build(1, 1, n);
    int l, r;
    string op;
    while (m--) {
        cin >> op >> l >> r;
        if (op == "Q") {
            cout << query(1, l, r).v << endl;
        } else {
            modify(1, l, r);
            // print();
        }
    }
    return 0;
}