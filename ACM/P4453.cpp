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

constexpr int N = 2e4 + 5000, M = 1e3 + 100, p = 2e4, MOD = 998244353;
int f[M][N];
int s[N];
int n;

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    ll ans = 0;
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i) {
        ++ans;
        for (int j = i - 1; j >= 1; --j) {
            int diff = s[i] - s[j] + p;
            f[i][diff] += f[j][diff] + 1;
            f[i][diff] %= MOD;
            ans += f[j][diff] + 1;
            ans %= MOD;
        }
    }
    cout << ans << endl;
    return 0;
}