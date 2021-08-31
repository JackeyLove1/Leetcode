#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <numeric>
#include <string>

using namespace std;

constexpr int MOD = 1e6 + 7, N = 500, M = 42;
int n, m;
int nums[N];
int card[5];
int f[M][M][M][M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    int x;
    for (int i = 1; i <= m; i++) {
        cin >> x;
        ++card[x];
    }

    // init
    f[0][0][0][0] = nums[1];
    for (int i = 0; i <= card[1]; i++) {
        for (int j = 0; j <= card[2]; j++) {
            for (int k = 0; k <= card[3]; k++) {
                for (int l = 0; l <= card[4]; l++) {
                    int r = 1 + i + 2 * j + 3 * k + 4 * l;
                    int t = nums[r];
                    if (i) f[i][j][k][l] = max(f[i - 1][j][k][l] + t, f[i][j][k][l]);
                    if (j) f[i][j][k][l] = max(f[i][j - 1][k][l] + t, f[i][j][k][l]);
                    if (k) f[i][j][k][l] = max(f[i][j][k - 1][l] + t, f[i][j][k][l]);
                    if (l) f[i][j][k][l] = max(f[i][j][k][l - 1] + t, f[i][j][k][l]);
                }
            }
        }
    }

    cout << f[card[1]][card[2]][card[3]][card[4]] << endl;
    return 0;
}