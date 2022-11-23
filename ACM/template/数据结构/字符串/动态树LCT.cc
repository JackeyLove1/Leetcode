#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 100010
#define fa(x) tr[x].p
#define lc(x) tr[x].s[0]
#define rc(x) tr[x].s[1]
#define notroot(x) lc(fa(x))==x||rc(fa(x))==x
int n, m;
struct node {
    int s[2], p, v, sum;
    int tag; //翻转懒标记
} tr[N];

void pushup(int x) {
    tr[x].sum = tr[lc(x)].sum
                ^ tr[x].v ^ tr[rc(x)].sum;
}

void pushdown(int x) {
    if (tr[x].tag) {
        swap(lc(x), rc(x));
        tr[lc(x)].tag ^= 1;
        tr[rc(x)].tag ^= 1;
        tr[x].tag = 0;
    }
}

void rotate(int x) {
    int y = fa(x), z = fa(y);
    int k = rc(y) == x;
    if (notroot(y))
        tr[z].s[rc(z) == y] = x;
    fa(x) = z;
    tr[y].s[k] = tr[x].s[k ^ 1];
    fa(tr[x].s[k ^ 1]) = y;
    tr[x].s[k ^ 1] = y;
    fa(y) = x;
    pushup(y), pushup(x);
}

void pushall(int x) {
    if (notroot(x)) pushall(fa(x));
    pushdown(x);
}

void splay(int x) {//伸展
    pushall(x);
    while (notroot(x)) {
        int y = fa(x), z = fa(y);
        if (notroot(y))
            (rc(y) == x) ^ (rc(z) == y)
            ? rotate(x) : rotate(y);
        rotate(x);
    }
}

void access(int x) {//通路
    for (int y = 0; x;) {
        splay(x);
        rc(x) = y;
        pushup(x);
        y = x, x = fa(x);
    }
}

void makeroot(int x) {//换根
    access(x);
    splay(x);
    tr[x].tag ^= 1; //打懒标记
}

void split(int x, int y) {//分离
    makeroot(x);
    access(y);
    splay(y);
}

void output(int x, int y) {
    split(x, y);
    printf("%d\n", tr[y].sum);
}

int findroot(int x) {//找根
    access(x);
    splay(x);
    while (lc(x))
        pushdown(x), x = lc(x);
    splay(x); //防止卡链
    return x;
}

void link(int x, int y) {//连边
    makeroot(x);
    if (findroot(y) != x) fa(x) = y;
}

void cut(int x, int y) {//断边
    makeroot(x);
    if (findroot(y) == x
        && fa(y) == x && !lc(y)) {
        fa(y) = 0;
        pushup(x);
    }
}

void change(int x, int y) {//修改
    splay(x);
    tr[x].v = y;
    pushup(x);
}

int main() {
    scanf("%d%d", &n, &m);
    // 初始时所有点都是孤立的
    for (int i = 1; i <= n; i++)
        scanf("%d", &tr[i].v);
    while (m--) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 0) output(x, y);
        else if (t == 1) link(x, y);
        else if (t == 2) cut(x, y);
        else change(x, y);
    }
}

/*
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
struct Node
{
    int s[2], p, v;
    int sum, rev;
}tr[N];
int stk[N];

void pushrev(int x)
{
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x)
{
    tr[x].sum = tr[tr[x].s[0]].sum ^ tr[x].v ^ tr[tr[x].s[1]].sum;
}

void pushdown(int x)
{
    if (tr[x].rev)
    {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

bool isroot(int x)
{
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x)
{
    int top = 0, r = x;
    stk[ ++ top] = r;
    while (!isroot(r)) stk[ ++ top] = r = tr[r].p;
    while (top) pushdown(stk[top -- ]);
    while (!isroot(x))
    {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
}

void access(int x)  // 建立一条从根到x的路径，同时将x变成splay的根节点
{
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p)
    {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x)  // 将x变成原树的根节点
{
    access(x);
    pushrev(x);
}

int findroot(int x)  // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
{
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y)  // 给x和y之间的路径建立一个splay，其根节点是y
{
    makeroot(x);
    access(y);
}

void link(int x, int y)  // 如果x和y不连通，则加入一条x和y之间的边
{
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}

void cut(int x, int y)  // 如果x和y之间存在边，则删除该边
{
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0])
    {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &tr[i].v);
    while (m -- )
    {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 0)
        {
            split(x, y);
            printf("%d\n", tr[y].sum);
        }
        else if (t == 1) link(x, y);
        else if (t == 2) cut(x, y);
        else
        {
            splay(x);
            tr[x].v = y;
            pushup(x);
        }
    }

    return 0;
}
*/