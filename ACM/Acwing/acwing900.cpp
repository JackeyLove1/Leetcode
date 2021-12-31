#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e3 + 100, MOD = 1e9 + 7;
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;

    // 初始化边界条件
    for (int i = 0; i <= n; i++) f[i][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = f[i - 1][j] % MOD;
            if (j >= i) f[i][j] = (f[i - 1][j] + f[i][j - i]) % MOD;
        }
    }

    cout << f[n][n] << endl;
    return 0;
}