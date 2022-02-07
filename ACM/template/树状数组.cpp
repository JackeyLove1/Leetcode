#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m;
int a[N];
LL tr[N];

int lowbit(int x)
{
    return x & -x;
}

void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

LL sum(int x)
{
    LL res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

// 创建求和树状数组时，加入数据的形式是差分的形式
    for (int i = 1; i <= n; i ++ ) add(i, a[i] - a[i - 1]);

    while (m -- )
    {
        char op[2];
        int l, r, d;
        scanf("%s%d", op, &l);
        if (*op == 'C')
        {
            scanf("%d%d", &r, &d);
            add(l, d), add(r + 1, -d);
        }
        else
        {
            printf("%lld\n", sum(l));
        }
    }

    return 0;
}