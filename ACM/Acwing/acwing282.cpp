#include <iostream>
#include <algorithm>

// 区间DP模版题

using namespace std;

const int N = 1e3 + 100;
int s[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) s[i] += s[i - 1]; // 计算前缀和

    for (int len = 2; len <= n; len++) {      //区间长度
        for (int i = 1; i + len - 1 <= n; i++) { //枚举起点
            int j = i + len - 1;                 //区间终点
            f[i][j] = 1e8;
            for (int k = i; k < j; k++) {        //枚举分割点，构造状态转移方程
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
            }
        }
    }

    cout << f[1][n] << endl;
    return 0;
}