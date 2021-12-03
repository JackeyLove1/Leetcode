#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

using bll = __int128;
constexpr int N = 20;
int n, m;
int g[N][N], f[N][N];
int path[N][N][N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
        }
    }
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= j; ++k) {
                if (f[i][j] < f[i - 1][k] + g[i][j - k]) {
                    f[i][j] = f[i - 1][k] + g[i][j - k];
                    for (int h = 1; h < i; h++) path[i][j][h] = path[i - 1][k][h];
                    path[i][j][i] = j - k;
                }
            }
        }
    }
    cout << f[n][m] << endl;
    for (int i = 1; i <= n; i++) cout << i << " " << path[n][m][i] << endl;
    return 0;
}