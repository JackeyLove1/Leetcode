// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2e3 + 100, INF = 0x3f3f3f3f;

#define N 100010
#define INF 1e9
#define ls(x) tr[x].s[0]
#define rs(x) tr[x].s[1]
int n, m;

struct node {
    int s[2]; //左右儿子
    int p; //父亲
    int v; //节点权值
    int cnt; //权值出现次数
    int siz; //子树大小
    void init(int p1, int v1) {
        p = p1, v = v1;
        cnt = siz = 1;
    }
} tr[N];

int root; //根节点编号
int idx; //节点个数

void pushup(int x) {
    tr[x].siz = tr[ls(x)].siz + tr[rs(x)].siz + tr[x].cnt;
}

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

void insert(int v) { //插入
    int x = root, p = 0;
    while (x && tr[x].v != v)
        p = x, x = tr[x].s[v > tr[x].v];
    if (x) tr[x].cnt++;
    else {
        x = ++idx;
        tr[p].s[v > tr[p].v] = x;
        tr[x].init(p, v);
    }
    splay(x, 0);
}

void find(int v) { //找到v并转到根
    int x = root;
    while (tr[x].s[v > tr[x].v] && v != tr[x].v)
        x = tr[x].s[v > tr[x].v];
    splay(x, 0);
}

int getpre(int v) { //前驱
    find(v);
    int x = root;
    if (tr[x].v < v) return x;
    x = ls(x);
    while (rs(x))x = rs(x);
    return x;
}

int getnxt(int v) { //后继
    find(v);
    int x = root;
    if (tr[x].v > v) return x;
    x = rs(x);
    while (ls(x))x = ls(x);
    return x;
}

void del(int v) { //删除
    int pre = getpre(v);
    int suc = getnxt(v);
    splay(pre, 0), splay(suc, pre);
    int del = tr[suc].s[0];
    if (tr[del].cnt > 1)
        tr[del].cnt--, splay(del, 0);
    else
        tr[suc].s[0] = 0, splay(suc, 0);
}

int getrank(int v) { //排名
    find(v);
    return tr[tr[root].s[0]].siz;
}

int getval(int k) { //数值
    int x = root;
    while (1) {
        int y = ls(x);
        if (tr[y].siz + tr[x].cnt < k)
            k -= tr[y].siz + tr[x].cnt,
                    x = rs(x);
        else if (tr[y].siz >= k) x = y;
        else break;
    }
    splay(x, 0);
    return tr[x].v;
}

int main() {
    insert(-INF);
    insert(INF); //哨兵
    scanf("%d", &n);
    while (n--) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) insert(x);
        if (op == 2) del(x);
        if (op == 3) printf("%d\n", getrank(x));
        if (op == 4) printf("%d\n", getval(x + 1));
        if (op == 5) printf("%d\n", tr[getpre(x)].v);
        if (op == 6) printf("%d\n", tr[getnxt(x)].v);
    }
    return 0;
}