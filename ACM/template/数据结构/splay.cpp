/*
#include <iostream>
using namespace std;

#define N 100010
#define INF 1e9
#define ls(x) tr[x].s[0]
#define rs(x) tr[x].s[1]
int n, m;
struct node{
  int s[2]; //左右儿子
  int p; //父亲
  int v; //节点权值
  int cnt; //权值出现次数
  int siz; //子树大小
  void init(int p1,int v1){
    p=p1, v=v1;
    cnt=siz=1;
  }
}tr[N];
int root; //根节点编号
int idx; //节点个数

void pushup(int x){
  tr[x].siz=tr[ls(x)].siz+tr[rs(x)].siz+tr[x].cnt;
}
void rotate(int x){
  int y=tr[x].p, z=tr[y].p;
  int k = tr[y].s[1]==x;
  tr[z].s[tr[z].s[1]==y] =x;
  tr[x].p = z;  
  tr[y].s[k] = tr[x].s[k^1];
  tr[tr[x].s[k^1]].p = y;
  tr[x].s[k^1] = y;
  tr[y].p = x;
  pushup(y), pushup(x);
}
void splay(int x, int k){
  while(tr[x].p!=k){
    int y=tr[x].p, z=tr[y].p;
    if(z!=k)   // 折转底，直转中
      (ls(y)==x)^(ls(z)==y)
        ? rotate(x) : rotate(y);
    rotate(x);
  }
  if(k==0) root = x;
}
void insert(int v){ //插入
  int x=root, p=0;
  while(x && tr[x].v!=v)
    p=x, x=tr[x].s[v>tr[x].v];
  if(x) tr[x].cnt++;
  else{
    x=++idx;
    tr[p].s[v>tr[p].v]=x;
    tr[x].init(p,v);
  }
  splay(x, 0);
}
void find(int v){ //找到v并转到根
  int x=root;
  while(tr[x].s[v>tr[x].v]&&v!=tr[x].v) 
    x=tr[x].s[v>tr[x].v]; 
  splay(x, 0);
}
int getpre(int v){ //前驱
  find(v);
  int x=root;
  if(tr[x].v<v) return x;
  x=ls(x);
  while(rs(x))x=rs(x);
  return x;
}
int getnxt(int v){ //后继
  find(v);
  int x=root;
  if(tr[x].v>v) return x;
  x=rs(x);
  while(ls(x))x=ls(x);
  return x;
}
void del(int v){ //删除
  int pre=getpre(v);
  int suc=getnxt(v);
  splay(pre,0), splay(suc,pre);
  int del=tr[suc].s[0];
  if(tr[del].cnt>1)
   tr[del].cnt--, splay(del,0);
  else
   tr[suc].s[0]=0,splay(suc,0);
}
int getrank(int v){ //排名
  find(v);
  return tr[tr[root].s[0]].siz;
}
int getval(int k){ //数值
  int x=root;
  while(1){
    int y=ls(x);
    if(tr[y].siz+tr[x].cnt<k)
      k -= tr[y].siz+tr[x].cnt,
      x = rs(x);
    else if(tr[y].siz>=k) x=y;
    else break;           
  }
  splay(x, 0);
  return tr[x].v;
}
int main(){
  insert(-INF);insert(INF); //哨兵
  scanf("%d", &n);
  while(n--){
    int op,x;
    scanf("%d%d", &op, &x);
    if(op==1) insert(x);
    if(op==2) del(x);
    if(op==3) printf("%d\n",getrank(x));
    if(op==4) printf("%d\n",getval(x+1));
    if(op==5) printf("%d\n",tr[getpre(x)].v);
    if(op==6) printf("%d\n",tr[getnxt(x)].v);
  }
  return 0;
}
*/
/*支持操作
插入操作
查询 x 的排名
查询排名 x 的数
查询前驱
查询后继
合并两棵树
删除操作
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
struct Node
{
    int s[2], p, v;//儿子,父节点,编号
    int size, flag;//子树节点个数, 有没有翻转

    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
}tr[N];
int root, idx;

void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void pushdown(int x)
{
    if (tr[x].flag)
    {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;
        tr[tr[x].s[1]].flag ^= 1;
        tr[x].flag = 0;
    }
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k) // spaly 操作，将x节点旋转到k节点之下
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

int insert(int v) // 将数据v插入，返回其编号
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    return u;
}

int get_k(int k) // 找到第k大的数据
{
    int u = root;
    while (true)
    {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

int get(int v) // 找到第一个大于等于v的数的编号
{
    int u = root, res;
    while (u)
    {
        if (tr[u].v >= v) res = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}

void output(int u)
{
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    if (tr[u].s[1]) output(tr[u].s[1]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i ++ ) insert(i);
    while (m -- )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_k(l), r = get_k(r + 2);
        (l, 0), (r, l);
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
    return 0;
}


/*
https://oi-wiki.org/ds//#%E6%9F%A5%E8%AF%A2-x-%E7%9A%84%E6%8E%92%E5%90%8D
查询排名 x 的数
设  为剩余排名，具体步骤如下：

如果左子树非空且剩余排名  不大于左子树的大小 ，那么向左子树查找。
否则将  减去左子树的和根的大小。如果此时  的值小于等于 ，则返回根节点的权值，否则继续向右子树查找。

查询前驱
前驱定义为小于  的最大的数，那么查询前驱可以转化为：将  插入（此时  已经在根的位置了），前驱即为  的左子树中最右边的节点，最后将  删除即可。

查询后继
后继定义为大于  的最小的数，查询方法和前驱类似： 的右子树中最左边的节点。

合并两棵树
合并两棵  树，设两棵树的根节点分别为  和 ，那么我们要求  树中的最大值小于  树中的最小值。合并操作如下：

如果  和  其中之一或两者都为空树，直接返回不为空的那一棵树的根节点或空树。
否则将  树中的最大值  到根，然后把它的右子树设置为  并更新节点的信息，然后返回这个节点。

删除操作
删除操作也是一个比较复杂的操作，具体步骤如下：

首先将  旋转到根的位置。

如果 （有不止一个 ），那么将  减  并退出。
否则，合并它的左右两棵子树即可。


*/
/*
插入
1  找到x插入位置
   把x转到根
2  将一个序列插到y的后面
    ---------------
            y z
    2.1 找y的后继z 
    2.2 将y转到根       (y,0)
    2.3 将z转到y的下面  spaly(z,y)
   y
    \
     z
    /
  null(因为z和y之间没有数,所以z左子树为空) 
   2.4 将序列插入到z的左子树 
删除
   -----------------
     L-1 L   R R+1
   1 将L-1转到根节点
   2 将R+1转到L-1下面
   此时R+1的左子树=[L,R]
   3 将R+1的左儿子置为空Null

*/

/*
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m;
struct Node
{
    int s[2], p, v;//儿子,父节点,编号
    int size, flag;//子树节点个数, 有没有翻转

    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
}tr[N];
int root, idx;

void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void pushdown(int x)
{
    // 如果当前子树需要翻转 48.34
    if (tr[x].flag)
    {
        //要翻转整颗子树，要先把左右两个儿子翻转，然后递归翻转左右两棵子树
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;//翻转标记往下传
        tr[tr[x].s[1]].flag ^= 1;//翻转标记往下传
        tr[x].flag = 0;//当前标记清空
    }
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;// 边1 z原来的儿子y变为x  x的父节点变为z
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;// 边3 y的左儿子变为x的右儿子B,x的右儿子的父节点变为y
    tr[x].s[k ^ 1] = y, tr[y].p = x;// 边2 x的右儿子变为y,y的父节点变为x
    pushup(y), pushup(x);// A,B,C三个点信息没变,但x,y子树信息变了,又y在x下面,所以先维护更新y子树,再维护更新x子树
}

void (int x, int k)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
        // 如果是折线关系  ==  x是y的右/左儿子 且 y是z的左/右儿子  一0一1
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);//折线rotate两次x
            else rotate(y);//直线rotate 一次y一次x
        rotate(x);
    }
    if (!k) root = x;//如果k==0 根节点更新为x
}
// 按大插右 小插左的二叉树插法 插入节点
void insert(int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];//一直往下递归直到u为null
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;//如果有父节点,父节点儿子信息更新为u
    tr[u].init(v, p);//初始化点u的值和父节点
    (u, 0);//插入后将当前点u转到根节点上
}

int get_k(int k)
{
    int u = root;
    while (true)
    {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;//找不到返回-1
}
//中序遍历
void output(int u)
{
    pushdown(u);
    // 如果u有左儿子 先递归输出左儿子
    if (tr[u].s[0]) output(tr[u].s[0]);
    // 如果u不是哨兵输出当前点
    if (tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    // 如果u有右儿子 递归输出右儿子
    if (tr[u].s[1]) output(tr[u].s[1]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i ++ ) insert(i);//插入哨兵 0,n+1 防止L-1和R+1越界
    while (m -- )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        //因为哨兵要翻转的从[L,R]变为[L+1,R+1] 则要找L和R+2作为L+1的前继和R+1的后继
        l = get_k(l), r = get_k(r + 2);
        // 左端点l转到根,右端点r转到左端点下面
        (l, 0), (r, l);
        // 只要将r的左子树[L+1,R+1]翻转
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
    return 0;
}

*/

/*
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010, INF = 1e9;

int n, m, delta;
struct Node
{
    int s[2], p, v;
    int size;

    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
}tr[N];
int root, idx;

void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

int insert(int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    return u;
}

int get(int v)
{
    int u = root, res;
    while (u)
    {
        if (tr[u].v >= v) res = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}

int get_k(int k)
{
    int u = root;
    while (u)
    {
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return tr[u].v;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

int main()
{
    scanf("%d%d", &n, &m);
    int L = insert(-INF), R = insert(INF);

    int tot = 0;
    while (n -- )
    {
        char op[2];
        int k;
        scanf("%s%d", op, &k);
        if (*op == 'I')
        {
            if (k >= m) k -= delta, insert(k), tot ++ ;
        }
        else if (*op == 'A') delta += k;
        else if (*op == 'S')
        {
            delta -= k;
            R = get(m - delta);
            splay(R, 0), splay(L, R);
            tr[L].s[1] = 0;
            pushup(L), pushup(R);
        }
        else
        {
            if (tr[root].size - 2 < k) puts("-1");
            else printf("%d\n", get_k(tr[root].size - k) + delta);
        }
    }

    printf("%d\n", tot - (tr[root].size - 2));

    return 0;
}
*/