#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>
#include <climits>

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

constexpr int N = 1e6 + 100;
ll w[N];
ll f[N], g[N];
ll l[N], r[N];
int n;

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    l[0] = INT64_MIN;
    r[n + 1] = INT64_MIN;
    for (int i = 1; i <= n; ++i) {
        f[i] = max(f[i - 1] + w[i], w[i]);
        l[i] = max(l[i - 1], f[i]);
    }
    for (int i = n; i >= 1; --i) {
        g[i] = max(w[i], g[i + 1] + w[i]);
        r[i] = max(r[i + 1], g[i]);
    }
    ll res = INT64_MIN;
    for (int i = 2; i < n; ++i) {
        res = max(l[i - 1] + r[i + 1], res);
    }
    cout << res << endl;
    return 0;
}