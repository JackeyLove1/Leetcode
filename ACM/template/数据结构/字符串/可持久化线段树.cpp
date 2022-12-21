#include <bits/stdc++.h>

using namespace std;

const int N = 100010, M = 10010;

int n, m;
int a[N];
vector<int> nums;

struct Node
{
    int l, r;
    int cnt;
}tr[N * 4 + N * 17];

int root[N], idx;

int find(int x) // get_id
{
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

int build(int l, int r)
{
    int p = ++ idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
}

int insert(int p, int l, int r, int x)
{
    int q = ++ idx;
    tr[q] = tr[p];
    if (l == r)
    {
        tr[q].cnt ++ ;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}

int query(int q, int p, int l, int r, int k)
{
    if (l == r) return r;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    root[0] = build(0, nums.size() - 1);

    for (int i = 1; i <= n; i ++ )
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));

    while (m -- )
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)]);
    }

    return 0;
}

/*
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e5;  // 数据范围
int tot, n, m;
int sum[(maxn << 5) + 10], rt[maxn + 10], ls[(maxn << 5) + 10],
    rs[(maxn << 5) + 10];
int a[maxn + 10], ind[maxn + 10], len;

inline int getid(const int &val) {  // 离散化
  return lower_bound(ind + 1, ind + len + 1, val) - ind;
}

int build(int l, int r) {  // 建树
  int root = ++tot;
  if (l == r) return root;
  int mid = l + r >> 1;
  ls[root] = build(l, mid);
  rs[root] = build(mid + 1, r);
  return root;  // 返回该子树的根节点
}

int update(int k, int l, int r, int root) {  // 插入操作
  int dir = ++tot;
  ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
  if (l == r) return dir;
  int mid = l + r >> 1;
  if (k <= mid)
    ls[dir] = update(k, l, mid, ls[dir]);
  else
    rs[dir] = update(k, mid + 1, r, rs[dir]);
  return dir;
}

int query(int u, int v, int l, int r, int k) {  // 查询操作
  int mid = l + r >> 1,
      x = sum[ls[v]] - sum[ls[u]];  // 通过区间减法得到左儿子中所存储的数值个数
  if (l == r) return l;
  if (k <= x)  // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
    return query(ls[u], ls[v], l, mid, k);
  else  // 否则说明在右儿子中
    return query(rs[u], rs[v], mid + 1, r, k - x);
}

inline void init() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  memcpy(ind, a, sizeof ind);
  sort(ind + 1, ind + n + 1);
  len = unique(ind + 1, ind + n + 1) - ind - 1;
  rt[0] = build(1, len);
  for (int i = 1; i <= n; ++i) rt[i] = update(getid(a[i]), 1, len, rt[i - 1]);
}

int l, r, k;

inline void work() {
  while (m--) {
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", ind[query(rt[l - 1], rt[r], 1, len, k)]);  // 回答询问
  }
}

int main() {
  init();
  work();
  return 0;
}
*/


/*
#pragma GCC optimize(2)
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;
int n, m;
int a[N];
vector<int> nums;

struct Node
{
    int l, r;
    int cnt;
}tr[N * 4 + N * 17];  //N * 4 + NlogN

int root[N], idx;

int find(int x)
{
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

// 对左右边界建立节点并编号, build是建立好骨架, 每个版本insert改不同数据
int build (int l, int r)
{
    int p = ++idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid+1, r);
    return p;
}

// l, r是要放入的坐标范围, x是要插入的数离散化后的位置
int insert(int p, int l, int r, int x)
{
    // 假设现在是从外界第一次执行insert, 那么调用的时候, p必定是根节点,
    // 那么q就相当于复制了一个根节点, 从节点q进入这棵树的时候, 也能得到之前的所有内容.
    // 同理, 再往下二分递归的时候, insert会继续复制根节点的左(右)子树, 一直递归直到l==r之前,
    // q和原来的p都是一毛一样. 直到l==r才真正插入了新点, 每次插入的时间空间复杂度都是lgk,
    // 总加起来就是lg1+lg2+...+lgn = lg(n!), 根据stirling公式, 结果为nlgn   (大O)
    int q = ++idx;
    tr[q] = tr[p]; 
    if (l == r)  // 如果区间长度为1, 说明就是放这里了
    {
        // tr[q].cnt++是表示插在这个叶节点上
        // 这个线段树只是保存的每个区间里面的元素个数
        // 每次插入都只是覆盖到的那堆区间里面的cnt发生+1
        tr[q].cnt++;
        return q;
    }

    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid+1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;  // 相当于pushup了
    return q;
}


// l ,r是检索范围, q是当前第r个节点root[r]能包含1~r之间所有
// p的输入是root[l-1], 作用是剔除这个根节点所包含数据的影响
int query(int q, int p, int l, int r, int k)
{
    if (l == r) return r; // 如果找到位置

    // 目标是求l r之间的第k小
    // tr[tr[q].l].cnt - tr[tr[p].l].cnt的结果是求出在p之后插入到q这些数之后,
    // 有多少个数(cnt)插入了p的左子树, 由于p的内容肯定不能出现在l r之间(p根节点就是root[l-1]), 
    // 所以cnt就是相当于"存在q左子树里面但不存在于1, l 之间的数的个数"
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt; 

    int mid = l + r >> 1;
    // k <= cnt说明要找的元素在q的左子树里面, 同时这里面也要剔除掉包含在p左子树的内容
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid+1, r, k - cnt);  // 类似同上
}


int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);  //离散化使用
    }

    // 离散化
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    // 构造线段树, 构造n个版本的线段树
    // 第0个版本的什么都没有就用build, build是建立好骨架, 每个版本insert改不同数据
    root[0] = build(0, nums.size() - 1);
    // 后面的每插入一个点算一个版本, 每次插入都只是比上一个版本多1个数
    // 左右参数给0和nums.size()-1是因为离散化之后的值域就是在0, nums.size()-1之间
    // 要插入必须得把这些地方全包才能保证找得到插入点
    for (int i = 1; i <= n; i++)
        root[i] = insert(root[i-1], 0, nums.size() - 1, find(a[i]));


    while (m -- )
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[r], root[l-1], 0, nums.size()-1, k)]);
    }
    return 0;
}
*/

/*
#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            sgn *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * sgn;
}

constexpr int N = 1e6 + 100;
struct Node {
    int l, r, v;
};
std::array<Node, N << 5> tr{};
std::array<int, N> root{}, A{};
int idx{0};
int n, m;

void pushup(int u) {
    // todo
    auto &root = tr[u], &left = tr[tr[u].l], &right = tr[tr[u].r];
}

int build(int l, int r) {
    int p = ++idx;
    if (l == r) {
        tr[p].v = A[l];
        return p;
    }
    int mid = l + r >> 1;
    tr[p].l = build(l, mid);
    tr[p].r = build(mid + 1, r);
    pushup(p);
    return p;
}


void pushdown() {
    // todo
}

int insert(int p, int l, int r, int k) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[r].v = k;
        return q;
    }
    int mid = l + r >> 1;
    tr[q].l = insert(tr[p].l, l, mid, k);
    tr[q].r = insert(tr[p].r, mid + 1, r, k);
    pushup(q);
    return q;
}

int update(int p, int l, int r, int x, int k) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[q].v = k;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = update(tr[p].l, l, mid, x, k);
    else tr[q].r = update(tr[p].r, mid + 1, r, x, k);
    pushup(q);
    return q;
}

int query(int p, int l, int r, int x) {
    if (tr[p].l <= l && r <= tr[p].r <= r) return tr[p].v;
    int mid = l + r >> 1;
    if (x <= mid) return query(tr[p].l, l, mid, x);
    else return query(tr[p].r, mid + 1, r, x);
}

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read();
    root[0] = build(1, n);
    for (int t = 1; t <= m; ++t) {
        int v = read(), o = read();
        if (o == 1) {
            int x = read(), k = read();
            root[t] = update(root[v], 1, n, x, k);
        } else {
            int x = read();
            root[t] = root[v];
            printf("%d\n", query(root[v], 1, n, x));
        }
    }
    return 0;
}
*/