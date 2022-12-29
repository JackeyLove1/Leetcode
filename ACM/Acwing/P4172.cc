#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 150010, INF = 1e9;

int n, m;

struct Edge {
    int x, y, c;

    bool operator<(const Edge &t) const {
        return c < t.c;
    }
} e[N];

struct Node {
    int s[2], p, v;
    int mx, rev;
} tr[N];
int stk[N], p[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void pushrev(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x) {
    tr[x].mx = x;
    for (int i = 0; i < 2; i++)
        if (tr[tr[tr[x].s[i]].mx].v > tr[tr[x].mx].v)
            tr[x].mx = tr[tr[x].s[i]].mx;
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
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

struct Query {
    int k, u, v;
};
using PII = pair<int, int>;
map<PII, int> edges;

void insert(int x, int y) {
    int id = edges[{x, y}];
    int c = e[id].c;
    if (find(x) == find(y)) {
        split(x, y);
        int t = tr[y].mx;
        if (tr[t].v > c) {
            cut(e[t - n].x, t), cut(t, e[t - n].y);
            link(x, n + id), link(n + id, y);
        }
    } else {
        p[find(x)] = find(y);
        link(x, n + id), link(n + id, y);
    }
}

int main() {
    fhj();
    int q;
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        if (x > y) std::swap(x, y);
        e[i] = {x, y, c};
    }
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; ++i) {
        edges[{e[i].x, e[i].y}] = i;
        p[i + n] = i + n;
        tr[i + n].mx = i + n, tr[i + n].v = e[i].c;
    }
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        tr[i].mx = i, tr[i].v = 0;
    }
    vector<Query> qs;
    qs.reserve(q);
    vector<int> res;
    res.reserve(q);
    set<PII> ks;
    for (int i = 0; i < q; ++i) {
        int k, u, v;
        cin >> k >> u >> v;
        if (u > v) std::swap(u, v);
        if (k == 2) ks.insert({u, v});
        qs.push_back({k, u, v});
    }
    for (int i = 1; i <= m; ++i) {
        int u = e[i].x, v = e[i].y, id = edges[{u, v}];
        if (ks.count({u, v})) continue;
        if (find(u) == find(v)) continue;
        p[find(u)] = find(v);
        link(u, id + n), link(id + n, v);
    }
    for (int i = q - 1; i >= 0; --i) {
        int k = qs[i].k, x = qs[i].u, y = qs[i].v;
        if (k == 2) {
            insert(x, y);
        } else {
            split(x, y);
            res.push_back(tr[tr[y].mx].v);
        }
    }
    reverse(res.begin(), res.end());
    for (const auto num: res) {
        cout << num << endl;
    }
    return 0;
}