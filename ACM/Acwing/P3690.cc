#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define fa(x) tr[x].p
#define lson(x) tr[x].s[0]
#define rson(x) tr[x].s[1]
int n, m;
struct node {
  int s[2], p, v, sum;
  int rev; //翻转懒标记
} tr[N];
inline bool isroot(int x) {
    return lson(fa(x)) != x && rson(fa(x)) != x;
}
inline void pushup(int x) { tr[x].sum = tr[lson(x)].sum ^ tr[x].v ^ tr[rson(x)].sum; }
void pushdown(int x) {
  if (tr[x].rev) {
    swap(lson(x), rson(x));
    tr[lson(x)].rev ^= 1;
    tr[rson(x)].rev ^= 1;
    tr[x].rev = 0;
  }
}
void rotate(int x) {
  int y = fa(x), z = fa(y);
  int k = rson(y) == x;
  if (!isroot(y))
    tr[z].s[rson(z) == y] = x;
  fa(x) = z;
  tr[y].s[k] = tr[x].s[k ^ 1];
  fa(tr[x].s[k ^ 1]) = y;
  tr[x].s[k ^ 1] = y;
  fa(y) = x;
  pushup(y), pushup(x);
}
void pushall(int x) {
  if (!isroot(x))
    pushall(fa(x));
  pushdown(x);
}
void splay(int x) { //伸展
  pushall(x);
  while (!isroot(x)) {
    int y = fa(x), z = fa(y);
    if (!isroot(y))
      (rson(y) == x) ^ (rson(z) == y) ? rotate(x) : rotate(y);
    rotate(x);
  }
}
void access(int x) { //通路
  for (int y = 0; x;) {
    splay(x);
    rson(x) = y;
    pushup(x);
    y = x, x = fa(x);
  }
}
void makeroot(int x) { //换根
  access(x);
  splay(x);
  tr[x].rev ^= 1; //打懒标记
}
void split(int x, int y) { //分离
  makeroot(x);
  access(y);
  splay(y);
}
void output(int x, int y) {
  split(x, y);
  printf("%d\n", tr[y].sum);
}
int findroot(int x) { //找根
  access(x);
  splay(x);
  while (lson(x))
    pushdown(x), x = lson(x);
  splay(x); //防止卡链
  return x;
}
void link(int x, int y) { //连边
  makeroot(x);
  if (findroot(y) != x)
    fa(x) = y;
}
void cut(int x, int y) { //断边
  makeroot(x);
  if (findroot(y) == x && fa(y) == x && !lson(y)) {
    fa(y) = 0;
    pushup(x);
  }
}
void change(int x, int y) { //修改
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
    if (t == 0)
      output(x, y);
    else if (t == 1)
      link(x, y);
    else if (t == 2)
      cut(x, y);
    else
      change(x, y);
  }
}