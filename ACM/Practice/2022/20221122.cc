namespace splay{
    // #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2e3 + 100, INF = 1e9 + 100;

struct node {
    int s[2];
    int size, cnt, v, p;

    void init(int v_, int p_) {
        v = v_, p = p_;
    }
} tr[N];

inline void pushup(int u) {

}

inline void pushdown(int u) {

}

int root{0}, idx{0};

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k) // spaly 操作，将x节点旋转到k节点之下
{
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

inline void find(int v){
    int x = root;
    while (tr[x].s[v > tr[x].v] && v != tr[x].v){
        x = tr[x].s[v > tr[x].v];
    }
    splay(x, 0);
}

inline void insert(int v){
    int x = root, p = 0;
    while (x && tr[x].v != v){
        p = x, x = tr[x].s[v > tr[x].v];
    }
    if (x) tr[x].cnt++;
    else{
        x = ++idx;
        tr[p].s[v > tr[p].v] = x;
        tr[x].init(v, p);
    }
    splay(x, 0);
}

inline int getprev(int v){
    find(v);
    int x = root;
    if (tr[x].v < v) return x;
    x = tr[x].s[1];
    while (tr[x].s[0]) x = tr[x].s[0];
    return x;
}

inline int getnext(int v){
    find(v);
    int x = root;
    if (tr[x].v > v) return x;
    x = tr[x].s[1];
    while (tr[x].s[0]) x = tr[x].s[0];
    return x;
}

inline void del(int v){
    int pre = getprev(v);
    int suc = getnext(v);
    splay(pre, 0), splay(suc, pre);
    int del = tr[suc].s[0];
    if (tr[del].cnt > 1){
        --tr[del].cnt, splay(del, 0);
    }else{
        tr[suc].s[0] = 0, splay(suc, 0);
    }
}

inline int getval(int k){
    int x = root;
    while (1){
        int y = tr[x].s[0];
        if (tr[y].size + tr[x].cnt < k){
            k -= tr[y].size + tr[x].cnt;
            x = tr[x].s[1];
        }else if (tr[y].size >= k) x = tr[x].s[0];
        else break;
    }
    splay(x, 0);
    return tr[x].v;
}

int main(){
    insert(-INF), insert(INF);
    int n;
    cin >> n;
    
}
}

namespace LCA{
constexpr int N = 2e3 + 100, INF = 1e9 + 100;

int h[N], e[N], ne[N], depth[N];
int fa[N][16];
int idx{0};

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void bfs(int u) {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[u] = 0;
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q.push(j);
                fa[j][0] = t;
                for (int k = 1; k <= 15; ++k) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

inline int lca(int a, int b) {
    if (depth[a] < depth[b]) std::swap(a, b);
    for (int k = 15; k >= 0; ++k) {
        if (depth[fa[a][k]] >= depth[b]) {
            a = fa[a][k];
        }
    }
    if (a == b) return a;
    for (int k = 15; k >= 0; --k) {
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    }
    return fa[a][0];
}
}

