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

constexpr int N = 110, MOD = 1e9 + 7;
int n;
int rmb[N], rp[N], times[N];
int f[N][N], g[N][N];

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> rmb[i] >> rp[i] >> times[i];
    }
    int m, r;
    cin >> m >> r;
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= rmb[i]; j--) {
            for (int k = r; k >= rp[i]; k--) {
                if (f[j][k] < f[j - rmb[i]][k - rp[i]] + 1) {
                    f[j][k] = f[j - rmb[i]][k - rp[i]] + 1;
                    g[j][k] = g[j - rmb[i]][k - rp[i]] + times[i];
                } else if (f[j][k] == f[j - rmb[i]][k - rp[i]] + 1) {
                    g[j][k] = min(g[j][k], g[j - rmb[i]][k - rp[i]] + times[i]);
                }
            }
        }
    }
    cout << g[m][r] << endl;
    return 0;
}