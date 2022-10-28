#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 110;

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


/*
// 高斯消元，把n行m列的矩阵化为行最简矩阵
for (int j = 0; j < m; ++j) // 枚举列
{
    int i;
    for (i = curi; i < n; ++i) // 找到非0元素
        if (A[i][j])
            break;
    if (A[i][j] == 0)
        continue;
    for (int k = 0; k < m; ++k) // 把非0元素所在行交换到当前行
        swap(A[i][k], A[curi][k]);
    for (int k = m - 1; k >= j; --k) // 把当前行都除以A[curi][j]，令A[curi][j]归一，注意循环顺序
        A[curi][k] /= A[curi][j];
    for (int i = 0; i < n; ++i) // 对其他行消元
        if (i != curi)
            for (int k = m - 1; k >= j; --k) // 注意循环顺序
                A[i][k] -= A[curi][k] * A[i][j];
    curi++;
}


#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

constexpr int N = 110;
double a[N][N], res[N];
int n;

bool gauss() {
    for (int i = 1; i <= n; ++i) {
        //枚举列（项）
        int max = i;
        for (int j = i + 1; j <= n; ++j) {
            //选出该列最大系数
            if (std::fabs(a[j][i]) > std::fabs(a[max][i])) {
                //fabs是取浮点数的绝对值的函数
                max = j;
            }
        }
        for (int j = 1; j <= n + 1; ++j) {
            // 交换
            swap(a[i][j], a[max][j]);
        }
        if (!a[i][i]) {
            //最大值等于0则说明该列都为0，肯定无解
            // puts("No Solution");
            return false;
        }
        for (int j = 1; j <= n; ++j) {
            //每一项都减去一个数（即加减消元）
            if (j != i) {
                double temp = a[j][i] / a[i][i];
                for (int k = i + 1; k <= n + 1; ++k) {
                    a[j][k] -= a[i][k] * temp;
                    //a[j][k]-=a[j][i]*a[i][k]/a[i][i];
                }
            }
        }
    }
    //上述操作结束后，矩阵会变成这样
    /*
    k1*a=e1
    k2*b=e2
    k3*c=e3
    k4*d=e4
    */
    //所以输出的结果要记得除以该项系数，消去常数
    for (int i = 1; i <= n; ++i) {
        res[i] = a[i][n + 1] / a[i][i];
        // printf("%.2lf\n", a[i][n + 1] / a[i][i]);
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            scanf("%lf", &a[i][j]);
        }
    }
    if (!gauss()) {
        cout << "No Solution" << endl;
    } else {
        for (int i = 1; i <= n; ++i) {
            printf("%.2lf\n", res[i]);
        }
    }
    return 0;
}
*/