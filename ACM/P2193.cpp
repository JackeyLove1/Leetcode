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

constexpr int N = 2010, MOD = 1e9 + 7;
int n, p;
ll f[N][N];

int main() {
    fhj();
    cin >> n >> p;
    memset(f, 0, sizeof f);
    ll res = 0;
    for (int i = 1; i <= n; ++i) f[i][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= p; ++j) {
            for (int k = 1; k <= i; ++k) {
                if (i % k == 0) {
                    f[i][j] = (f[i][j] + f[i / k][j - 1]) % MOD;
                }
            }
        }
        res = (res + f[i][p]) % MOD;
    }
    cout << res << endl;
    return 0;
}