#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 45000, M = 50;

int primes[N], cnt;
bool st[N];

PII factor[M];
int cntf;

int divider[N], cntd;

void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

void dfs(int u, int p)
{
    if (u > cntf)
    {
        divider[cntd ++ ] = p;
        return;
    }

    for (int i = 0; i <= factor[u].second; i ++ )
    {
        dfs(u + 1, p);
        p *= factor[u].first;
    }
}

int main()
{
    get_primes(N);

    int n;
    scanf("%d", &n);
    while (n -- )
    {
        int a0, a1, b0, b1;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);

        int d = b1;
        cntf = 0;
        for (int i = 0; primes[i] <= d / primes[i]; i ++ )
        {
            int p = primes[i];
            if (d % p == 0)
            {
                int s = 0;
                while (d % p == 0) s ++, d /= p;
                factor[ ++ cntf] = {p, s};
            }
        }
        if (d > 1) factor[ ++ cntf] = {d, 1};

        cntd = 0;
        dfs(1, 1);

        int res = 0;
        for (int i = 0; i < cntd; i ++ )
        {
            int x = divider[i];
            if (gcd(x, a0) == a1 && (LL)x * b0 / gcd(x, b0) == b1)
            {

                res ++ ;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}
