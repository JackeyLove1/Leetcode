#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 220;
int f[N][N], g[N][N];
int a[N], s[N];
int n;

int main() {
    fhj();
    cin >> n;
    memset(f, -0x3f, sizeof f);
    memset(g, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; ++i) {
        s[i] = s[i - 1] + a[i];
    }
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= 2 * n; ++i) {
            if (len == 1) {
                f[i][i] = g[i][i] = 0;
                continue;
            }
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
                g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j] + s[j] - s[i - 1]);
            }
        }
    }
    int minn = INT_MAX, maxn = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        minn = min(minn, g[i][i + n - 1]);
        maxn = max(maxn, f[i][i + n - 1]);
    }
    cout << minn << endl;
    cout << maxn << endl;
    return 0;
}