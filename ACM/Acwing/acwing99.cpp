// Author: Jacky
// Time: 2021-09-18
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

constexpr int N = 1e4 + 100;
int t, r;
int n, m;
int g[N][N], s[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t >> r;
    for (int i = 0; i < t; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        ++x, ++y;
        g[x][y] += w;
        n = max(x, n), m = max(y, m);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + g[i][j];
        }
    }

    int res = 0;
    r = min({n, m, r});
    for (int i = r; i <= n; ++i) {
        for (int j = r; j <= m; ++j) {
            int tp = s[i][j] - s[i - r][j] - s[i][j - r] + s[i - r][j - r];
            res = max(res, tp);
        }
    }
    cout << res << endl;
    return 0;
}