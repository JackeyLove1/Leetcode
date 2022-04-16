#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
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

constexpr int N = 2200;
int a[N], b[N];
int f[N][N];
int n, m;
constexpr int INF = 0x3f3f3f3f;

inline int work() {
    // memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i) {
        int minv = INT_MAX;
        for (int j = 1; j <= n; ++j) {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = minv + abs(a[i] - b[j]);
        }
    }
    int res = INT_MAX;
    for (int i = 1; i <= n; ++i) res = min(res, f[n][i]);
    return res;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int res = work();
    reverse(a + 1, a + 1 + n);
    res = min(res, work());
    cout << res << endl;
    return 0;
}