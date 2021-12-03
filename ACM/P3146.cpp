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

using bll = __int128;

inline int read() {
    int X = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + ch - '0', ch = getchar();
    return X * w;
}

void print(bll x) {
    if (!x) return;
    if (x) print(x / 10);
    putchar(x % 10 + '0');
}

constexpr int N = 300, M = 1e3 + 100, INF = 0x3f3f3f3f;

int n, m;
int f[N][N];

int main() {
    fhj();
    cin >> n;
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i) {
        cin >> f[i][i];
    }
    int ans = 0;
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                if (f[i][k] == f[k + 1][j] && f[i][k] && f[k + 1][j]) {
                    f[i][j] = max(f[i][j], f[i][k] + 1);
                    ans = max(ans, f[i][j]);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}