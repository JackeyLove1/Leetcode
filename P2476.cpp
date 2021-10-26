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

constexpr int N = 16, MOD = 1e9 + 7;

ll f[N][N][N][N][N][N];
int n;

inline ll solve(int a, int b, int c, int d, int e, int last) {
    ll &v = f[a][b][c][d][e][last];
    if (v != -1) return v;
    if (a + b + c + d + e == 0) return v = 1;
    v = 0;
    if (a) v += (a - (last == 2)) * solve(a - 1, b, c, d, e, 1);
    if (b) v += (b - (last == 3)) * solve(a + 1, b - 1, c, d, e, 2);
    if (c) v += (c - (last == 4)) * solve(a, b + 1, c - 1, d, e, 3);
    if (d) v += (d - (last == 5)) * solve(a, b, c + 1, d - 1, e, 4);
    if (e) v += e * solve(a, b, c, d + 1, e - 1, 5);
    v %= MOD;
    return v;
}

int main() {
    fhj();
    cin >> n;
    int x;
    int t[6] = {0};
    for (int i = 0; i < n; ++i) {
        cin >> x;
        ++t[x];
    }
    memset(f, -1, sizeof f);
    cout << solve(t[1], t[2], t[3], t[4], t[5], 0) << endl;
    return 0;
}