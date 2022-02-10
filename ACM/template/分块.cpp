#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>

// 一个简单的整数问题2
/*
给定一个长度为 N 的数列 A，以及 M 条指令，每条指令可能是以下两种之一：
C l r d，表示把 A[l],A[l+1],…,A[r] 都加上 d。
Q l r，表示询问数列中第 l∼r 个数的和。
对于每个询问，输出一个整数表示答案。
*/

using namespace std;

typedef long long LL;
const int N = 100010, M = 350;

int n, m, len;
LL add[M], sum[M];
int w[N];

int get(int i) // 获取在那个分块
{
    return i / len;
}

void change(int l, int r, int d)
{
    if (get(l) == get(r))  // 段内直接暴力
    {
        for (int i = l; i <= r; i ++ ) w[i] += d, sum[get(i)] += d;
    }
    else
    {
        int i = l, j = r;
        while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, i ++ ;
        while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, j -- ;
        for (int k = get(i); k <= get(j); k ++ ) sum[k] += len * d, add[k] += d;
    }
}

LL query(int l, int r)
{
    LL res = 0;
    if (get(l) == get(r))  // 段内直接暴力
    {
        for (int i = l; i <= r; i ++ ) res += w[i] + add[get(i)];
    }
    else
    {
        int i = l, j = r;
        while (get(i) == get(l)) res += w[i] + add[get(i)], i ++ ;
        while (get(j) == get(r)) res += w[j] + add[get(j)], j -- ;
        for (int k = get(i); k <= get(j); k ++ ) res += sum[k];
    }
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &w[i]);
        sum[get(i)] += w[i];
    }

    char op[2];
    int l, r, d;
    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C')
        {
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", query(l, r));
    }

    return 0;
}

