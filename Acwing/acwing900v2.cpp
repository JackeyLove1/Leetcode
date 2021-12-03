#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <numeric>
#include <string>

using namespace std;

constexpr int MOD = 1e9 + 7;
constexpr int N = 1e3 + 100;
int n;
int f[N][N];

int main() {
    cin >> n;
    for (int i = 0; i <= n; i++) f[i][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= i) f[i][j] = (f[i][j] + f[i][j - i]) % MOD;
        }
    }

    cout << f[n][n] << endl;
    return 0;
}