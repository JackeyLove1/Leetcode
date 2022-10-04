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

constexpr int N = 1e5 + 100;
int n, m, p;

struct Node {
    int l, r;
    int ls, rs, ms;

    friend ostream &operator<<(ostream &os, const Node &node) {
        os << "l: " << node.l << " r: " << node.r << " ms: " << node.ms;
        return os;
    }
} tr[N * 4];

int w[N];

void pushup(Node &root, Node &left, Node &right) {
    root.ls = left.ls, root.rs = right.rs;
    root.ms = std::max({left.ms,right.ms});
    // 区间合并的条件
    if (w[left.r] < w[right.l]) {
        // 如果左区间连续
        if (left.ls == left.r - left.l + 1) {
            root.ls += right.ls;
        }
        // 如果右区间连续
        if (right.rs == right.r - right.l + 1) {
            root.rs += left.rs;
        }
        // left.rs + right.ls可以拼接到一起
        // cout <<"Update root before: " << root << endl;
        root.ms = std::max({root.ms, right.ls, right.rs, left.rs + right.ls});
        // cout <<"Update root after: " << root << endl;
    }
}

void pushup(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    pushup(root, left, right);
}


void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    // todo
}


void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, 1, 1, 1};
        // cout <<"Build: " << tr[u] << endl;
    } else {
        tr[u] = {l, r, 0, 0, 0};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
        // cout <<"Build: " << tr[u] << endl;
    }
}


Node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        // cout << tr[u] << endl;
        return tr[u];
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        if (l > mid) return query(u << 1 | 1, l, r);
        auto left = query(u << 1, l, r);
        auto right = query(u << 1 | 1, l, r);
        // cout <<"Query: ";
        // cout << "left: " << left << " ";
        // cout << "right: " << right <<" ";
        Node res = {left.l, right.r, 0};
        pushup(res, left, right);
        return res;
    }
}

void modify(int u, int x, int d) {
    if (tr[u].l == x && tr[u].r == x) {
        w[x] = d;
        // cout <<"Modify: " << tr[u] << endl;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, d);
        else modify(u << 1 | 1, x, d);
        pushup(u);
        // cout <<"Update: " << tr[u] << endl;
    }
}

void print() {
    for (int u = 1; u <= n; ++u) {
        cout << tr[u] << endl;
    }
    cout << endl;
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> w[i];
        build(1, 1, n);
        string op;
        int l, r;
        while (m--) {
            cin >> op >> l >> r;
            if (op == "Q") {
                ++l, ++r;
                cout << query(1, l, r).ms << endl;
            } else {
                ++l;
                modify(1, l, r);
            }
        }
    }
    return 0;
}
