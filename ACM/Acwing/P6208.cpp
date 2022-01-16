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

constexpr int N = 1100, INF = 1e9;
int n, m;
int g[N][N];
int f[N][N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
        }
    }
    // memset(f, 0, sizeof f);
    f[1][1] = g[1][1];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n && j <= i; j++) {
            f[j][i] = max(f[j - 1][i - 1], max(f[j + 1][i - 1], f[j][i - 1])) + g[j][i];
        }
    }
    cout << f[n][m] << endl;
    return 0;
}