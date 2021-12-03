#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 100;
int n, m1, m2;
int v1[N], v2[N], w[N];
int f[500][500];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> m1 >> m2;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> v1[i] >> v2[i] >> w[i];
        for (int j = m1; j >= v1[i]; j--) {
            for (int k = m2; k >= v2[i]; k--) {
                f[j][k] = max(f[j][k], f[j - v1[i]][k - v2[i]] + w[i]);
            }
        }
    }

    cout << f[m1][m2] << endl;
    return 0;
}