#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510, INF = 1e9;

int n;
int a[N][N];
int f[N][N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= i; j ++ )
            scanf("%d", &a[i][j]);

    for (int i = 0; i <= n; i ++ )
        for (int j = 0; j <= i + 1; j ++ )
            f[i][j] = -INF;

    f[1][1] = a[1][1];
    for (int i = 2; i <= n; i ++ )
        for (int j = 1; j <= i; j ++ )
            f[i][j] = max(f[i - 1][j - 1] + a[i][j], f[i - 1][j] + a[i][j]);

    int res = -INF;
    for (int i = 1; i <= n; i ++ ) res = max(res, f[n][i]);

    printf("%d\n", res);
    return 0;
}
