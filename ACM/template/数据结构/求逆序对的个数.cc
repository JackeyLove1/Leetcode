#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int a[N], tmp[N];

LL merge_sort(int q[], int l, int r)
{
    if (l >= r) return 0;

    int mid = l + r >> 1;

    LL res = merge_sort(q, l, mid) + merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else
        {
            res += mid - i + 1;
            tmp[k ++ ] = q[j ++ ];
        }
    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];

    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);

    cout << merge_sort(a, 0, n - 1) << endl;

    return 0;
}

/*
// 线段树解
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

constexpr int N = 100000 + 100;
int n, m, p;

struct Node {
    int l, r;
    ll v;

    friend ostream &operator<<(ostream &os, const Node &node) {
        os << "l: " << node.l << " r: " << node.r << " v: " << node.v;
        return os;
    }
} tr[N * 4];

int w[N], c[N];

void pushup(Node &root, Node &left, Node &right) {
    root.v = left.v + right.v;
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
        tr[u] = {l, r, 0};
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}


Node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        // cout << tr[u] << endl;
        return tr[u];
    }
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
        tr[u].v += d;
        // cout <<"Modify: " << tr[u] << endl;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, d);
        else modify(u << 1 | 1, x, d);
        pushup(u);
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
    cin >> n;
    vector<int> v(n, 0);
    unordered_map<int, int> index;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        v[i - 1] = w[i];
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 0; i < v.size(); ++i) {
        index[v[i]] = i + 1;
    }
    const int sz = v.size();
    build(1, 1, sz);
    ull sum = 0;
    for (int i = n; i >= 1; --i) {
        auto idx = index[w[i]];
        if (idx == 1) {
            modify(1,1,1);
            continue;
        }
        auto node = query(1, 1, idx - 1);
        // cout << "Query " << node << endl;
        sum += node.v;
        modify(1, idx, 1);
    }
    cout << sum << endl;
    return 0;
}
*/