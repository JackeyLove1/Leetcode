#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
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

constexpr int N = 220;
using ll = long long;
ll f[N][N];

inline ll qms(int a, int b) {
    a = static_cast<ll>(a);
    b = static_cast<ll>(b);
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int n, m;
int a[N], b[N];
ll ksm[N][N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            // A[i] * (x ^ B[i])
            ksm[i][j] = 1l * a[i] * qms(j, b[i]);
        }
    }
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i <= m; ++i) f[i][0] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= j; ++k) {
                f[i][j] = min(f[i][j], f[i - 1][j - k] + ksm[i][k]);
            }
        }
    }
    ll res = INT64_MAX;
    for (int i = 1; i <= m; ++i) res = min(res, f[i][n]);
    cout << res << endl;
    return 0;
}