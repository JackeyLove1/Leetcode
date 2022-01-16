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

constexpr int N = 2050;
int n;
int f[N][N], s[N];

int solve(int l, int r, int d) {
    if (r < l) return 0;
    int &v = f[l][r];
    if (v != -1) return v;
    if (l == r) return v = s[l] * d;
    v = max(solve(l + 1, r, d + 1) + d * s[l],
            solve(l, r - 1, d + 1) + d * s[r]);
    return v;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    memset(f, -1, sizeof f);
    solve(1, n, 1);
    cout << f[1][n] << endl;
    return 0;
}