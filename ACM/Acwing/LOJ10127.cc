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

constexpr int N = 200010;
int n, m, p;

struct Node {
    int l, r;
    ll v;
} tr[N * 4];

int nums[N];

void build(int u, int l, int r) {
    tr[u] = {l, r, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void pushup(int u) {
    tr[u].v = std::max(tr[u << 1].v, tr[u << 1 | 1].v);
}

void pushdown(int u) {
    // todo
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int mid = tr[u].l + tr[u].r >> 1;
    ll v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = std::max(v, query(u << 1 | 1, l, r));
    return v;
}

void modify(int u, int x, int d) {
    if (tr[u].l == x && tr[u].r == x) tr[u].v = d;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, d);
        else modify(u << 1 | 1, x, d);
        pushup(u);
    }
}

int main() {
    fhj();
    int last = 0;
    n = 0;
    cin >> m >> p;
    string op;
    int x;
    build(1, 1, m + 1);
    while (m--){
        cin >> op >> x;
        if (op == "Q"){
            last = query(1, n - x  + 1, n);
            cout << last << endl;
        }else{
            modify(1, n + 1, (1ll * x + last) % p);
            ++n;
        }
        // cout << "op: " << op <<" x: " << x << endl;
    }
    return 0;
}