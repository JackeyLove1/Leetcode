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

constexpr int N = 1e4 + 100, M = 2e5 + 100;
short f[N][N];

int solve(int x, int y, int MOD) {
    if (f[x][y] == -1) return 3;
    short &v = f[x][y];
    if (v) return v;
    v = -1;
    if (x == 0) return v =1;
    if (y == 0) return v = 2;
    int x0 = (x + y) % MOD;
    int y0 = (x0 + y) % MOD;
    return v = solve(x0, y0, MOD);
}

int main() {
    fhj();
    int n, mod;
    cin >> n >> mod;
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        int v = solve(x, y, mod);
        if (v == 1) {
            cout << 1 << endl;
        } else if (v == 2) {
            cout << 2 << endl;
        } else {
            cout << "error" << endl;
        }
    }
    return 0;
}