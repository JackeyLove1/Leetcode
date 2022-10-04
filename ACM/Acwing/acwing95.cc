#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

constexpr int N = 1e5 + 100;

int g[10][10], tmp[10][10];

inline bool check(int x, int y) {
    if (x < 1 || x > 5 || y < 1 || y > 5) return false;
    return true;
}

constexpr int dx[]{0, 0, 1, 0, -1}, dy[]{0, 1, 0, -1, 0};

inline void change(int x, int y) {
    for (int i = 0; i < 5; ++i) {
        auto nx = x + dx[i], ny = y + dy[i];
        if (check(nx, ny)) {
            g[nx][ny] = std::abs(1 - g[nx][ny]);
        }
    }
}

inline bool judge() {
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            if (!g[i][j]) return false;
        }
    }
    return true;
}

inline void print() {
    cout << "Print: " << endl;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}

inline void solve() {
    memset(g, 0, sizeof g);
    char c;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            cin >> c;
            g[i][j] = c - '0';
        }
    }
    memcpy(tmp, g, sizeof g);
    int res = INT32_MAX;
    for (int i = 0; i < (1 << 5); ++i) {
        int cnt = 0;
        // cout << "i: " << i << endl;
        for (int j = 0; j < 5; ++j) {
            if ((1 << j) & i) {
                change(1, j);
                ++cnt;
                // cout << "change " << 1 << " " << j << endl;
                // print();
            }
        }
        // cout << " second " << endl;
        for (int j = 1; j <= 4; ++j) {
            for (int k = 1; k <= 5; ++k) {
                if (!g[j][k]) {
                    // cout << "before" << endl;
                    // print();
                    change(j+1, k), ++cnt;
                    // cout << "after change " << j << " " << k << endl;
                    // print();
                }
            }
        }
        if (judge()) {
            // print();
            // cout << "i: " << i << " cnt: " << cnt << endl;
            res = std::min(res, cnt);
        }
        memcpy(g, tmp, sizeof g);
    }
    if (res > 0 && res <= 6) cout << res << endl;
    else cout << -1 << endl;
}

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}