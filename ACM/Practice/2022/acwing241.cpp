#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <list>
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

static inline int cnt_(int x) {
    return __builtin_popcount(x);
}

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 200010, M = 3100010;

int n;
int a[N], tr[N];
int great[N], low[N];

inline int lowbit(int x) {
    return x & (-x);
}

inline void add(int x, int c) {
    for (int pos = x; pos <= n; pos += lowbit(pos)) {
        tr[pos] += c;
    }
}

inline int sum(int x) {
    int res = 0;
    for (int pos = x; pos; pos -= lowbit(pos)) {
        res += tr[pos];
    }
    return res;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        int y = a[i];
        great[i] = sum(n) - sum(y);
        low[i] = sum(y - 1);
        add(y, 1);
    }
    // reverse traverse
    ll res1 = 0, res2 = 0;
    memset(tr, 0, sizeof tr);
    for (int i = n; i > 0; --i) {
        int y = a[i];
        res1 += 1l * great[i] * (sum(n) - sum(y));
        res2 += 1l * low[i] * (sum(y - 1));
        add(y, 1);
    }
    cout << res1 << " " << res2 << endl;
    return 0;

}