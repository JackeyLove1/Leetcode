#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100005;
//d 为离散化数组
int n, m, len, a[N], d[N];

//T[i] 为 [1, i] 区间的权值线段树的根节点
int T[N], tot = 0;

//线段树的每个点
struct SegTree{
    int l, r, v;
}t[N * 20];

//建树
int build(int l, int r){
    int p = ++tot, mid = (l + r) >> 1;
    if(l < r) {
        t[p].l = build(l, mid);
        t[p].r = build(mid + 1, r);
    }
    t[p].v = 0; return p;
}

//增加一个数 pre 为上一个的根节点。
int update(int pre, int l, int r, int v){
    int p = ++tot, mid = (l + r) >> 1;
    t[p].l = t[pre].l, t[p].r = t[pre].r, t[p].v = t[pre].v + 1;
    if(l < r){
        //应该更新哪一个值域区间
        if(v <= mid) t[p].l = update(t[pre].l, l, mid, v);
        else t[p].r = update(t[pre].r, mid + 1, r, v); 
    }
    return p;
}

//查询
int query(int x, int y, int l, int r, int k){
    //找到了
    if(l == r) return l;
    //对位相减
    int sum = t[t[y].l].v - t[t[x].l].v, mid = (l + r) >> 1;
    if(k <= sum) return query(t[x].l, t[y].l, l, mid, k);
    else return query(t[x].r, t[y].r, mid + 1, r, k - sum);
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i), d[i] = a[i];
    //离散化
    sort(d + 1, d + 1 + n);
    len = unique(d + 1, d + 1 + n) - (d + 1);
    for(int i = 1; i <= n; i++) 
        a[i] = lower_bound(d + 1, d + 1 + len, a[i]) - d;


    T[0] = build(1, len);
    for(int i = 1; i <= n; i++)
        T[i] = update(T[i - 1], 1, len, a[i]);

    //回答
    while(m--){
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        int ans = query(T[l - 1], T[r], 1, len, k);
        printf("%d\n", d[ans]);
    }
    return 0;
}
