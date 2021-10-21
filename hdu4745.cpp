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

constexpr int N = 2e3 + 100, M = 220, INF = 0x7fffffff;

int q[N], f[N][N];
const int debug = 0;

int solve(int i, int j) {
    if (i > j) return 0;
    if (i == j) return 1;
    int &v = f[i][j];
    if (v != -1) return v;
    v = 0;
    if (q[i] == q[j]) {
        v = max(v, solve(i + 1, j - 1) + 2);
    }
    v = max(v, max(solve(i + 1, j), solve(i, j - 1)));
    if (debug) {
        cout << "i: " << i << " j: " << j << " res: " << v << endl;
    }
    return v;
}

int main() {
    fhj();
    int n;
    while (cin >> n && n) {
        memset(q, 0, sizeof q);
        memset(f, -1, sizeof f);
        for (int i = 1; i <= n; ++i) {
            // break the chain
            cin >> q[i];
            q[i + n] = q[i];
        }
        if (debug) {
            for (int i = 1; i <= 2 * n; ++i) cout << q[i] << " ";
            cout << endl;
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res = max(res, solve(1, i) + solve(i + 1, n));
        }
        cout << res << endl;
    }
    return 0;
}