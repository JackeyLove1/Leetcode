// 权值线段树套区间线段树
// 权值线段树维护 权值-下标映射
// 区间线段树维护 区间-权值映射
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 50010, P = N * 17 * 17, M = N * 4;

int n, m;
struct Tree
{
    int l, r, sum, add;
}tr[P];
int L[M], R[M], T[M], idx;
struct Query
{
    int op, a, b, c;
}q[N];
vector<int> nums;

int get(int x)
{
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

void build(int u, int l, int r)
{
    L[u] = l, R[u] = r, T[u] = ++ idx;
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int intersection(int a, int b, int c, int d)
{
    return std::min(b, d) - std::max(a, c) + 1;
}

void update(int u, int l, int r, int pl, int pr)
{
    tr[u].sum += intersection(l, r, pl, pr);
    if (l >= pl && r <= pr)
    {
        tr[u].add ++ ;
        return;
    }
    int mid = l + r >> 1;
    if (pl <= mid)
    {
        if (!tr[u].l) tr[u].l = ++ idx;
        update(tr[u].l, l, mid, pl, pr);
    }
    if (pr > mid)
    {
        if (!tr[u].r) tr[u].r = ++ idx;
        update(tr[u].r, mid + 1, r, pl, pr);
    }
}

void change(int u, int a, int b, int c)
{
    update(T[u], 1, n, a, b);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (c <= mid) change(u << 1, a, b, c);
    else change(u << 1 | 1, a, b, c);
}

int get_sum(int u, int l, int r, int pl, int pr, int add)
{
    if (l >= pl && r <= pr) return tr[u].sum + (r - l + 1) * add;
    int mid = l + r >> 1, res = 0;
    add += tr[u].add;
    if (pl <= mid)
    {
        if (tr[u].l) res += get_sum(tr[u].l, l, mid, pl, pr, add);
        else res += intersection(l, mid, pl, pr) * add;
    }
    if (pr > mid)
    {
        if (tr[u].r) res += get_sum(tr[u].r, mid + 1, r, pl, pr, add);
        else res += intersection(mid + 1, r, pl, pr) * add;
    }
    return res;
}

int query(int u, int a, int b, int c)
{
    if (L[u] == R[u]) return R[u];
    int mid = L[u] + R[u] >> 1;
    int k = get_sum(T[u << 1 | 1], 1, n, a, b, 0);
    if (k >= c) return query(u << 1 | 1, a, b, c);
    return query(u << 1, a, b, c - k);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++ )
    {
        scanf("%d%d%d%d", &q[i].op, &q[i].a, &q[i].b, &q[i].c);
        if (q[i].op == 1) nums.push_back(q[i].c);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    build(1, 0, nums.size() - 1);

    for (int i = 0; i < m; i ++ )
    {
        int op = q[i].op, a = q[i].a, b = q[i].b, c = q[i].c;
        if (op == 1) change(1, a, b, get(c));
        else printf("%d\n", nums[query(1, a, b, c)]);
    }
    return 0;
}

/*
using namespace std;
typedef long long ll;
const int inf = 0x7fffffff;
const int N=5e4+5;
const int Tree=N*400;
int n,m,node=0,totn;
int ql[N],qr[N],op[N],b[N],k[N];
int rt[N<<2],tag[Tree];
ll sz[Tree];
struct Tnode{
    int L,R;
}T[Tree];
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
#define lc p<<1
#define rc p<<1|1
inline void pushdown(int p,int l,int r){
    int &v=tag[p],mid=(l+r)>>1;
    if (!T[p].L)T[p].L=++node;
    if (!T[p].R)T[p].R=++node;
    tag[T[p].L]+=v,tag[T[p].R]+=v;
    sz[T[p].L]+=v*(mid-l+1),sz[T[p].R]+=v*(r-mid);
    v=0;
}
inline void update(int &p,int ql,int qr,int l=1,int r=n){
    if (!p)p=++node;
    if (ql<=l && r<=qr){
        ++tag[p];sz[p]+=r-l+1;
        return;
    }
    if (tag[p])pushdown(p,l,r);
    rint mid=(l+r)>>1;
    if (ql<=mid) update(T[p].L,ql,qr,l,mid);
    if (mid<qr) update(T[p].R,ql,qr,mid+1,r);
    sz[p]=sz[T[p].L]+sz[T[p].R];
}
inline ll getsum(int &p,int ql,int qr,int l=1,int r=n){
    if (!p)return 0;
    if (ql<=l && r<=qr) return sz[p];
    if (tag[p])pushdown(p,l,r);
    rint mid=(l+r)>>1;
    ll tt=0;
    if (ql<=mid) tt+=getsum(T[p].L,ql,qr,l,mid);
    if (mid<qr) tt+=getsum(T[p].R,ql,qr,mid+1,r);
    return tt;
}
inline void add(int ql,int qr,int k,int p=1,int l=1,int r=totn){
    update(rt[p],ql,qr);
    if (l==r) return;
    rint mid=(l+r)>>1;
    if (k<=mid) add(ql,qr,k,lc,l,mid);
        else add(ql,qr,k,rc,mid+1,r);
}
inline int query(int ql,int qr,ll k,int p=1,int l=1,int r=totn){
    if (l==r) return b[l];
    rint mid=(l+r)>>1;
    ll tt=getsum(rt[rc],ql,qr);
    if (tt<k) return query(ql,qr,k-tt,lc,l,mid);
        else return query(ql,qr,k,rc,mid+1,r);
}
int main(){
    n=read(),m=read();
    for (rint i=1;i<=m;++i){
        op[i]=read(),ql[i]=read(),qr[i]=read(),k[i]=read();
        if (op[i]==1)b[++totn]=k[i];
    }
    sort(b+1,b+totn+1);
    totn=unique(b+1,b+totn+1)-b-1;
    for (rint i=1;i<=m;++i)
        if (op[i]==1)k[i]=lower_bound(b+1,b+totn+1,k[i])-b;
    for (rint i=1;i<=m;++i){
        if (op[i]==1){
            add(ql[i],qr[i],k[i]);
        }else{
            printf("%d\n",query(ql[i],qr[i],k[i]));
        }
    }
    return 0;
}
*/

/*
// 权值线段树套区间线段树
// 权值线段树维护 权值-下标映射
// 区间线段树维护 区间-权值映射
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 50010, P = N * 400, M = N * 5;
int n, m;
struct Tree {
    int lson, rson, sum, add;
} tr[P];                   // 区间线段树
int L[M], R[M], T[M], idx; // 权值线段树
struct Query {
    int op, a, b, c;
} q[N];
vector<int> nums;

inline int get(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

inline void pushup(int u) { tr[u].sum = tr[tr[u].lson].sum + tr[tr[u].rson].sum; }

void pushdown(int u, int l, int r) {
    if (!tr[u].lson) tr[u].lson = ++idx;
    if (!tr[u].rson) tr[u].rson = ++idx;
    auto &root = tr[u], &left = tr[tr[u].lson], &right = tr[tr[u].rson];
    if (root.add) {
        int mid = l + r >> 1;
        left.add += root.add, left.sum += (mid - l + 1) * root.add;
        right.add += root.add, right.sum += (r - mid) * root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    L[u] = l, R[u] = r, T[u] = ++idx;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int l, int r, int ql, int qr, int d) {
    if (l >= ql && r <= qr) {
        tr[u].sum += (r - l + 1) * d;
        tr[u].add += d;
    } else    // 一定要分裂
    {
        pushdown(u, l, r);
        int mid = l + r >> 1;
        if (l <= mid) {
            modify(tr[u].lson, l, mid, ql, qr, d);
        }
        if (r > mid) {
            modify(tr[u].rson, mid + 1, r, ql, qr, d);
        }
        pushup(u);
    }
}

int query(int u, int l, int r, int ql, int qr) {
    if (ql >= l && r <= qr) return tr[u].sum;
    pushdown(u, l, r);
    int mid = l + r >> 1;
    int sum = 0;
    if (ql <= mid) {
        if (!tr[u].lson) tr[u].lson = ++idx;
        sum = query(tr[u].lson, l, mid, ql, qr);
    }
    if (qr > mid) {
        if (!tr[u].rson) tr[u].rson = ++idx;
        sum += query(tr[u].rson, mid + 1, r, ql, qr);
    }
    return sum;
}

// 第 a 个位置到第 b 个位置的权值线段树，每个位置加入一个数 c
void change(int u, int a, int b, int c) {
    // updatePart(T[u], 1, n, a, b);
    modify(T[u], 1, n, a, b, 1);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (c > mid) change(u << 1 | 1, a, b, c);
    else change(u << 1, a, b, c);
}

int queryPartSum(int u, int l, int r, int ql, int qr, int add) {
    return query(u, l, r, ql, qr);
}

int query(int u, int a, int b, int c) {
    if (L[u] == R[u]) return L[u];
    int k = queryPartSum(T[u << 1 | 1], 1, n, a, b, 0);
    if (k >= c) return query(u << 1 | 1, a, b, c);
    else return query(u << 1, a, b, c - k);
}

int main() {
    fhj();
    cin >> n >> m;
    memset(T, 0, sizeof T), memset(L, 0, sizeof L), memset(R, 0, sizeof R);
    nums.reserve(n);
    for (int i = 0; i < m; ++i) {
        cin >> q[i].op >> q[i].a >> q[i].b >> q[i].c;
        if (q[i].op == 1) {
            nums.push_back(q[i].c);
        }
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    build(1, 0, nums.size() - 1);
    for (int i = 0; i < m; ++i) {
        if (q[i].op == 1) {
            change(1, q[i].a, q[i].b, get(q[i].c));
        } else {
            cout << nums[query(1, q[i].a, q[i].b, q[i].c)] << endl;
        }
    }
    return 0;
}
*/