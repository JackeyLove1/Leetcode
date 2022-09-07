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
            // 高斯消元的过程，将这一位得1所有数都消成0
                a[j] ^= a[k];
        k ++ ;
        if (k == n) break;
    }

    LL res = 0;
    // 消去之后异或求得最大值
    for (int i = 0; i < k; i ++ ) res ^= a[i];
    printf("%lld\n", res);
    return 0;
}
