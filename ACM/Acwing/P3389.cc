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
        cout << "No Solution";
    } else {
        for (int i = 1; i <= n; ++i) {
            printf("%.2lf\n", res[i]);
        }
    }
    return 0;
}