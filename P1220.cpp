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

constexpr int N = 55, M = 2e5 + 100;

int a[N], b[N], s[N];
int f[N][N][2];

int main() {
    fhj();
    int n, c;
    cin >> n >> c;
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        s[i] = s[i - 1] + b[i];
    }
    f[c][c][0] = f[c][c][1] = 0;
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            f[i][j][0] = min(f[i + 1][j][0] + (a[i + 1] - a[i]) * (s[i] + s[n] - s[j]),
                             f[i + 1][j][1] + (a[j] - a[i]) * (s[i] + s[n] - s[j]));
            f[i][j][1] = min(f[i][j - 1][0] + (a[j] - a[i]) * (s[i - 1] + s[n] - s[j - 1]),
                             f[i][j - 1][1] + (a[j] - a[j - 1]) * (s[i - 1] + s[n] - s[j - 1]));
        }
    }
    cout << min(f[1][n][0], f[1][n][1]) << endl;
    return 0;
}