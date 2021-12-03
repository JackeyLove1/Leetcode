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

constexpr int N = 1e3 + 10, MOD = 1e9 + 7;
int s[N], f[N][3][32];
int n, m;

int solve(int a, int b, int c) {
    if (a > n) return 0;
    int &v = f[a][b][c];
    if (v != -1) return v;
    v = 0;
    if (c < m) {
        v = max(v, solve(a + 1, -1 * b + 3, c + 1) + int(-1 * b + 3 == s[a]));
    }
    v = max(v, solve(a + 1, b, c) + int(b == s[a]));
    return v;
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    memset(f, -1, sizeof f);
    cout << max(solve(1, 0, 0), solve(1, 1, 0)) << endl;
    return 0;
}