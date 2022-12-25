#include <bits/stdc++.h>

using namespace std;

constexpr int N = 150010, INF = 1e8;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

int n, m;

// Edge
struct Edge {
    int x, y, a, b;

    const bool operator<(const Edge &rhs) const {
        return a < rhs.a;
    }
} e[N];

// union Set
int p[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

// LCT
struct Node {
    int s[2], p, v;
    int rev, mv; // mv 这颗splay最大节点对应的编号
} tr[N];
int stk[N];

void pushrev(int x) {
    std::swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x) {
    // tr[x].sum = tr[tr[x].s[0]].sum ^ tr[x].v ^ tr[tr[x].s[1]].sum;
    for (int i = 0; i < 2; ++i) {
        if (tr[tr[x].s[i]].mv && tr[tr[tr[x].s[i]].mv].v > tr[tr[x].mv].v) {
            tr[x].mv = tr[tr[x].s[i]].mv;
        }
    }
}

void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

// 保证虚边不变
inline bool isroot(int x) { return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x; }

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y))
        tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r))
        stk[++top] = r = tr[r].p;
    while (top)
        pushdown(stk[top--]);
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y))
                rotate(x);
            else
                rotate(y);
        rotate(x);
    }
}

void access(int x) // 建立一条从根到x的路径，同时将x变成splay的根节点
{
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x) // 将x变成原树的根节点
{
    access(x);
    pushrev(x);
}

int findroot(int x) // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
{
    access(x);
    while (tr[x].s[0])
        pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y) // 给x和y之间的路径建立一个splay，其根节点是y
{
    makeroot(x);
    access(y);
}

void link(int x, int y) // 如果x和y不连通，则加入一条x和y之间的边
{
    makeroot(x);
    if (findroot(y) != x)
        tr[x].p = y;
}

void cut(int x, int y) // 如果x和y之间存在边，则删除该边
{
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

// 将x节点的值修改为w
void change(int x, int w) {
    splay(x);
    tr[x].v = w;
    pushup(x);
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].x >> e[i].y >> e[i].a >> e[i].b;
    }
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n + m; ++i) {
        p[i] = i;
        tr[i].mv = i;
        if (i > n) tr[i].v = e[i - n].b;
    }
    int res = INF;
    for (int i = 1; i <= m; ++i) {
        int x = e[i].x, y = e[i].y, a = e[i].a, b = e[i].b;
        if (find(x) == find(y)) {
            split(x, y);
            int t = tr[y].mv;
            if (tr[t].v > b){
                cut(e[t - n].x, t), cut(t, e[t - n].y);
                link(x, i + n), link(i + n, y);
            }
        } else {
            p[x] = y;
            link(x, i + n), link(i + n, y);
        }
        if (find(1) == find(n)) {
            split(1, n);
            res = std::min(res, a + tr[tr[n].mv].v);
        }
    }
    if (res == INF) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}
