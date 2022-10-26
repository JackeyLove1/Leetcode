#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 100010;

int n;
LL a[N];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%lld", &a[i]);

    int k = 0;
    // 高斯消元的过程
    // 从高位往低位进行枚举，找到第一个该位是1的数然后把这个数交换上来
    for (int i = 62; i >= 0; i -- )
    {
        for (int j = k; j < n; j ++ )
            if (a[j] >> i & 1)
            {
                swap(a[j], a[k]);
                break;
            }
        if (!(a[k] >> i & 1)) continue;
        for (int j = 0; j < n; j ++ )
            if (j != k && (a[j] >> i & 1))
                a[j] ^= a[k]; // 线性消元
        k ++ ;
        if (k == n) break;
    }

    LL res = 0;
    for (int i = 0; i < k; i ++ ) res ^= a[i];
    printf("%lld\n", res);
    return 0;
}

/*
constexpr int N = 1e5 + 100;
int n;
ll a[N];
ll liner[63];

inline void get_liner_base() {
    int k = 0;
    for (int i = 62; i >= 0; --i) {
        for (int j = k; j < n; ++j) {
            if ((a[j] >> i) & 1) {
                liner[++k] = a[j];
                break;
            }
        }
        if (!((liner[k] >> i) & 1)) continue;
        for (int j = 0; j < n; ++j) {
            if (((a[j] >> i) & 1)) {
                a[j] ^= liner[k];
            }
        }
        ++k;
        if (k == n) break;
    }
}
*/

// 求第k大的异或就是将k进行二进制分解即可

/*
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 10010;

int n, m;
LL a[N], p[N];
int cnt, flag;

void add(LL x)
{   
    for (int i = 62; i >= 0; i -- )
        if (x & (1ll << i))
            if (a[i]) x ^= a[i];
            else 
            {
                a[i] = x;
                return;
            }
    flag = 1;
}

void rebuild()
{
    for (int i = 62; i; i -- )
        if (a[i])
            for (int j = 62; j >= 0; j -- )
                if (i != j && a[i] & (1ll << j))
                    a[i] ^= a[j];

    for (int i = 0; i <= 62; i ++ )
        if (a[i])
            p[cnt ++ ] = a[i];
}

LL kth(LL k)
{
    if (flag) k -- ;
    if (k == 0) return 0;
    if (k >= (1ll << cnt)) return -1;
    LL res = 0;
    for (int i = 0; i < cnt; i ++ )
        if (k & (1ll << i))
            res ^= p[i];
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int ca = 1; ca <= T; ca ++ )
    {
        printf("Case #%d:\n", ca);

        memset(a, 0, sizeof a);
        flag = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i ++ )
        {
            LL x;
            scanf("%lld", &x);
            add(x);
        }

        cnt = 0;
        rebuild();

        scanf("%d", &m);
        while (m -- )
        {
            LL k;
            scanf("%lld", &k);
            printf("%lld\n", kth(k));
        }
    }

    return 0;
}
*/