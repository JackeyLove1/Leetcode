#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 55;
int g[N][N];
int f[N][N][N * 2];
int n, m;

int main() {
    fhj();
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> g[i][j];
        }
    }
    for (int k = 2; k <= m + n; ++k) {
        for (int i1 = 1; i1 < k && i1 <= m; ++i1) {
            for (int i2 = 1; i2 < k && i2 <= m; ++i2) {
                int score = g[i1][k - i1];
                if (i1 != i2) {
                    score += g[i2][k - i2];
                }
                f[i1][i2][k] = max({f[i1 - 1][i2][k - 1],
                                    f[i1][i2 - 1][k - 1],
                                    f[i1][i2][k - 1],
                                    f[i1 - 1][i2 - 1][k - 1]})
                               + score;
            }
        }
    }
    cout << f[m][m][m + n] << endl;
    return 0;
}