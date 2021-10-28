// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 5505;
int n, w, s;
ll f[N][N], a[N];

int main() {
    fhj();
    cin >> n >> w >> s;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    memset(f, -0x3f, sizeof f);
    // cout << f[1][1] << endl;
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = w; j >= 0; j--) {
            for (int k = min(w, j + s - 1); k >= j - 1; k--) {
                f[i][j] = max(f[i][j], f[i - 1][k] + a[i] * j);
            }
        }
    }
    ll ans = INT64_MIN;
    for (int i = 0; i <= w; ++i) {
        ans = max(ans, f[n][i]);
    }
    cout << ans << endl;
    return 0;
}