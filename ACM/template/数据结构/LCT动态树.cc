/*
给定 n 个点以及每个点的权值，要你处理接下来的 m 个操作。
操作有四种，操作从 0 到 3 编号。点从 1 到 n 编号。

0 x y 代表询问从 xx 到 yy 的路径上的点的权值的 xor 和。保证 xx 到 yy 是联通的。
1 x y 代表连接 xx 到 yy，若 xx 到 yy 已经联通则无需连接。
2 x y 代表删除边 (x,y)(x,y)，不保证边 (x,y)(x,y) 存在。
3 x y 代表将点 xx 上的权值变成 yy。

*/
#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m;
struct Node {
  int s[2], p, v;
  int sum, rev;
} tr[N];
int stk[N];

void pushrev(int x) {
  swap(tr[x].s[0], tr[x].s[1]);
  tr[x].rev ^= 1;
}

void pushup(int x) {
  tr[x].sum = tr[tr[x].s[0]].sum ^ tr[x].v ^ tr[tr[x].s[1]].sum;
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

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &tr[i].v);
  while (m--) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    if (t == 0) {
      split(x, y);
      printf("%d\n", tr[y].sum);
    } else if (t == 1)
      link(x, y);
    else if (t == 2)
      cut(x, y);
    else {
      splay(x);
      tr[x].v = y;
      pushup(x);
    }
  }

  return 0;
}
