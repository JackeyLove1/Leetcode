#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 150010, INF = 1e9;

int n, m;

struct Edge {
    int x, y, a, b;

    bool operator<(const Edge &rhs) const {
        return a < rhs.a;
    }
} e[N];

struct Node {
    int s[2], p, v;
    int mx, rev;
} tr[N];
int stk[N], p[N];

int find(int x) {
    if (p[x] != x) return p[x] = find(p[x]);
    return x;
}

void pushrev(int x) {
    if (tr[x].rev) {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[x].rev ^= 1;
    }
}

void pushup(int x) {
    tr[x].mx = x;
    for (int i = 0; i < 2; ++i) {
        if (tr[tr[tr[x].s[0]].mx].v > tr[tr[x].mx].v) {
            tr[x].mx = tr[tr[x].s[i]].mx;
        }
    }
}

void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

bool isroot(int x) {
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r)) stk[++top] = r = tr[r].p;
    while (top) pushdown(stk[top--]);
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
}

void access(int x) {
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x) {
    access(x);
    pushrev(x);
}

int findroot(int x) {
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y) {
    makeroot(x);
    access(y);
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}

void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[1]) {
        tr[y].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

int main() {
    // TODO
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        e[i] = {x, y, a, b};
    }
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        if (i > n) tr[i].v = e[i - n].b;
        tr[i].mx = i;
    }
    int res = INF;
    for (int i = 1; i <= m; ++i) {
        // int x = e[i].x, y = e[i].y, a = e[i].a, b = e[i].b;
        auto &[x, y, a, b] = e[i];
        if (find(x) == find(y)) {
            split(x, y);
            int t = tr[y].mx;
            if (tr[t].v > b) {
                cut(e[t - n].x, t), cut(t, e[t - n].y);
                link(x, n + i), link(n + i, y);
            }
        } else {
            p[find(x)] = find(y);
            link(n + i, x), link(n + i, y);
        }

        if (find(i) == find(n)) {
            split(1, n);
            res = min(res, a + tr[tr[n].mx].v);
            break;
        }
    }
    if (res == INF) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}