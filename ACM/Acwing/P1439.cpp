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

constexpr int N = 1e5 + 10, M = 2e5 + 100;

int n;
int a[N], b[N];
int f[N][N];
int ans = 0;

int solve(int x, int y) {
    int &v = f[x][y];
    if (v != -1) return v;
    if (x == 0 || y == 0) return v = 0;
    if (a[x] == b[y]) {
        v = max(v, solve(x - 1, y - 1) + 1);
    }
    v = max(v, solve(x - 1, y));
    v = max(v, solve(x, y - 1));
    ans = max(ans, v);
    // cout << "x: " << x << " y: " << y << " res: " << v << endl;
    return v;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    memset(f, -1, sizeof f);
    solve(n, n);
    cout << ans << endl;
    return 0;
}