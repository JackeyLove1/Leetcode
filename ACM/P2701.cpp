#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

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

constexpr int N = 1100, MOD = 1e9 + 7, M = 1e7 + 100;
int n, t;
int f[N][N];
int g[N][N];

int main() {
    fhj();
    cin >> n >> t;
    int a, b;
    memset(g, 1, sizeof g);
    while (t--) {
        cin >> a >> b;
        g[a][b] = 0;
    }
    int res = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][j]) {
                f[i][j] = min({f[i - 1][j], f[i][j - 1], f[i - 1][j - 1]}) + 1;
            }
            res = max(res, f[i][j]);
        }
    }
    cout << res << endl;
    return 0;
}