#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 15;

int n;
double a[N][N], b[N][N];

void gauss()
{
    // 转化成上三角矩阵
    for (int r = 1, c = 1; c <= n; c ++, r ++ )
    {
        // 找主元
        int t = r;
        for (int i = r + 1; i <= n; i ++ )
            if (fabs(b[i][c]) > fabs(b[t][c]))
                t = i;

        // 交换
        for (int i = c; i <= n + 1; i ++ ) swap(b[t][i], b[r][i]);
        // 归一化
        for (int i = n + 1; i >= c; i -- ) b[r][i] /= b[r][c];
        // 消
        for (int i = r + 1; i <= n; i ++ )
            for (int j = n + 1; j >= c; j -- )
                b[i][j] -= b[i][c] * b[r][j];
    }

    // 转化成对角矩阵
    for (int i = n; i > 1; i -- )
        for (int j = i - 1; j; j -- )
        {
            b[j][n + 1] -= b[i][n + 1] * b[j][i];
            b[j][i] = 0;
        }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n + 1; i ++ )
        for (int j = 1; j <= n; j ++ )
            scanf("%lf", &a[i][j]);

// 构建系数矩阵
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
        {
            b[i][j] += 2 * (a[i][j] - a[0][j]);
            b[i][n + 1] += a[i][j] * a[i][j] - a[0][j] * a[0][j];
        }

// 高斯消元
    gauss();

// 输出结果
    for (int i = 1; i <= n; i ++ ) printf("%.3lf ", b[i][n + 1]);

    return 0;
}
