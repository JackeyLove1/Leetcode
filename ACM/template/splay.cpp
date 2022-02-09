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

void insert(int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
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
    return -1;
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
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
    return 0;
}




平衡二叉树
set/map 红黑树(代码长) == splay(代码适中,支持很多操作)
treap(有局限,一些操作做不了)
AVL
多叉树
B树 B+树

操作:
    左旋 
    右旋 (维护的是中序遍历不变)
             右旋
              ->
         z           z
        /           //
       y           x    
      / \         / \\
     x   c       A   y
    / \            // \
   A   B           B   C
   AxByc           AxByc
             左旋
              ->
   =线代表变得关系
   -代表不变的关系
   可以发现由于要维护中序遍历,最左和最右的关系是不变的
    插入
    查询
⭐ 每操作一个节点 均将该节点旋转到树根
splay(x,k) 将点x旋转至点k下
1   
       z      y    x
      /      / \    \ 
     y      x   z    y
    /                 \
   x                   z    
        先转y     转x
    每转一次x往上走两格 直到某个点下面为止
2     z       z   x
     /       /   / \
    y       x   y   z
     \     /
      x   y
       先转x     转x

插入
1  找到x插入位置
   把x转到根
2  将一个序列插到y的后面
    ---------------
            y z
    2.1 找y的后继z 
    2.2 将y转到根       splay(y,0)
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
本题
维护信息
   1 子树总点数 size 用于递归查找位置
   2 懒标记     flag 整个区间是否需要翻转

pushup(u)用两个儿子信息维护根节点信息
  tr[u].size = tr[u<<1].size+tr[u<<1|1].size
写在旋转最后

pushdown(u)下传懒标记,先更新子树
    swap(tr[u<<1],tr[u<<1|1])(要翻转整颗子树，要先把左右两个儿子翻转，然后递归翻转左右两棵子树)
    将标记下传 t[u<<1] = t[u<<1|1] = t[u]
    将当前标记清空  t[u] = 0
写在递归之前

splay保证中序遍历是当前序列的顺序
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

/*
          z
         /
        y
       /
      x  
    k=0表示x是y的左儿子；k=1表示x是y的右儿子
         z           z
        /           //   --1
       y           x    
      / \         / \\   --2
     x   c       A   y
    / \      3--   // \
   A   B           B   C 
   AxByc           AxByc
             左旋
              ->
   =线代表变得关系
   -代表不变的关系
   可以发现由于要维护中序遍历,最左和最右的关系是不变的
   体现在rotate中就三条边
   k代表左,k^1代表右
*/
void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;// 边1 z原来的儿子y变为x  x的父节点变为z
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;// 边3 y的左儿子变为x的右儿子B,x的右儿子的父节点变为y
    tr[x].s[k ^ 1] = y, tr[y].p = x;// 边2 x的右儿子变为y,y的父节点变为x
    pushup(y), pushup(x);// A,B,C三个点信息没变,但x,y子树信息变了,又y在x下面,所以先维护更新y子树,再维护更新x子树
}
/*
1   
       z      y    x
      /      / \    \ 
     y      x   z    y
    /                 \
   x                   z    
        先转y     转x
    每转一次x往上走两格 直到某个点下面为止
2     z       z   x
     /       /   / \
    y       x   y   z
     \     /
      x   y
       先转x     转x
*/
void splay(int x, int k)
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
    splay(u, 0);//插入后将当前点u转到根节点上
}
/*
                 k
                / \
 tr[u<<1].size    
 如果左子树个数>=k 则去左子树里看
 如果左子树个数=k-1,则u就是中序遍历第k个点
 否则去右子树里看,k-=tr[u<<1].size-1
*/
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
        splay(l, 0), splay(r, l);
        // 只要将r的左子树[L+1,R+1]翻转
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);
    return 0;
}
