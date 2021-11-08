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

constexpr int N = 11000, MOD = 1e9 + 7, M = 1e7 + 100;
int s, m, n;
int v[N], cost[N];
ll f[M];

int main() {
    fhj();
    cin >> s >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> cost[i] >> v[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = cost[j]; k <= s; ++k) {
                f[k] = max(f[k], f[k - cost[j]] + v[j]);
            }
        }
        s += f[s];
    }
    cout << s << endl;
    return 0;
}
