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
#include <array>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using ll = long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 300010, INF = 1e9;

int n, m;
int w[N];
struct Node {
    int l, r;
    ll max;
} tr[N * 4];

void pushup(int u) {
    tr[u].max = std::max(tr[u << 1].max, tr[u << 1 | 1].max);
}

void pushdown(int u) {

}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, -INF};
    else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].max = d;
    } else    // 一定要分裂
    {
        // pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].max;
    // pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll maxv = -INF;
    if (l <= mid) maxv = std::max(maxv, query(u << 1, l, r));
    if (r > mid) maxv = std::max(maxv, query(u << 1 | 1, l, r));
    return maxv;
}


int main() {
    scanf("%d%d", &n, &m);
    build(1, 1, 2e5);
    char op[2];
    int t, len = 0;
    ll last = 0;
    while (n--) {
        scanf("%s%d", op, &t);
        if (*op == 'A') {
            ++len;
            t = (t + last) % m;
            modify(1, len, len, t);
        } else {
            auto l = len - t + 1, r = len;
            auto res = query(1, l, r);
            printf("%lld\n", res);
            last = res;
        }
    }
    return 0;
}

