#include <iostream>

using namespace std;

const int N = 150, mod = 1000;

int k, x;
int f[1000][100][N];

int qmi(int a, int b) {
    int res = 1;
    for (int i = b; i; i >>= 1) {
        if (i & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
// 高精度 a = b + c
void add(int a[N], int b[N], int c[N]) {
    for (int i = 0, t = 0; i < N; ++ i) {
        t += b[i] + c[i];
        a[i] = t % 10;
        t /= 10;
    }
}
int main() {
    cin >> k >> x;

    //求n = x^x
    int n = qmi(x % mod, x);

    //求组合数C(n-1,k-1)
    //递推式C(i,j) = C(i-1,j-1) + C(i-1,j)
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j <= i && j < k; ++ j) {
            if (!j) f[i][j][0] = 1;
            else add(f[i][j], f[i - 1][j], f[i - 1][j - 1]);
        }
    }

    //输出答案C(n-1,k-1)
    int it = N - 1;
    while (!f[n - 1][k - 1][it]) -- it;
    while (it >= 0) cout << f[n - 1][k - 1][it -- ];
    return 0;
}
