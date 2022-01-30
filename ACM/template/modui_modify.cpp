#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 10010, S = 1000010;

int n, m, mq, mc, len;
int w[N], cnt[S], ans[N];
struct Query
{
    int id, l, r, t;
}q[N];
struct Modify
{
    int p, c; // 修改的位置和修改后的值
}c[N];

int get(int x)
{
    return x / len;
}

// 排序：先左后右再时间戳
bool cmp(const Query& a, const Query& b)
{
    int al = get(a.l), ar = get(a.r);
    int bl = get(b.l), br = get(b.r);
    if (al != bl) return al < bl;
    if (ar != br) return ar < br;
    return a.t < b.t;
}

// 修改函数
void add(int x, int& res)
{
    if (!cnt[x]) res ++ ;
    cnt[x] ++ ;
}

void del(int x, int& res)
{
    cnt[x] -- ;
    if (!cnt[x]) res -- ;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    for (int i = 0; i < m; i ++ )
    {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'Q') mq ++, q[mq] = {mq, a, b, mc};
        else c[ ++ mc] = {a, b};
    }

    len = cbrt((double)n * mc) + 1;
    sort(q + 1, q + mq + 1, cmp);

    for (int i = 0, j = 1, t = 0, k = 1, res = 0; k <= mq; k ++ )
    {
        // 基础莫队
        int id = q[k].id, l = q[k].l, r = q[k].r, tm = q[k].t;
        while (i < r) add(w[ ++ i], res);
        while (i > r) del(w[i -- ], res);
        while (j < l) del(w[j ++ ], res);
        while (j > l) add(w[ -- j], res);
        // 如果当前时间戳小于需要的时间戳
        // 那么修改
        while (t < tm)
        {
            t ++ ;
            if (c[t].p >= j && c[t].p <= i)
            // 判断修改的位置是否在范围内
            {
                del(w[c[t].p], res);
                add(c[t].c, res);
            }
            swap(w[c[t].p], c[t].c);
        }
        // 如果当前的时间戳大于需要的时间戳
        // 那么回滚
        while (t > tm)
        {
            if (c[t].p >= j && c[t].p <= i)
            {
                del(w[c[t].p], res);
                add(c[t].c, res);
            }
            swap(w[c[t].p], c[t].c);
            t -- ;
        }
        ans[id] = res;
    }

    for (int i = 1; i <= mq; i ++ ) printf("%d\n", ans[i]);
    return 0;
}