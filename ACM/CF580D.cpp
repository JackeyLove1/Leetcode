#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int _count(int state) {
    return __builtin_popcount(state);
}

int n, m, k;
int a[20], g[20][20];
using ll = long long;
ll f[(1 << 18) + 10][20];
int x, y, c;

int main() {
    fhj();
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        f[1 << i][i] = a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> x >> y >> c;
        --x, --y;
        g[x][y] = c;
    }
    ll res = 0;
    for (int state = 0; state < (1 << n); ++state) {
        if (_count(state) > m) continue;
        for (int i = 0; i < n; ++i) {
            if (state & (1 << i)) {
                for (int j = 0; j < n; ++j) {
                    if (!(state & (1 << j))) {
                        auto state2 = state | (1 << j);
                        f[state2][j] = max(f[state2][j], f[state][i] + a[j] + g[i][j]);
                        // cout << "s2: " << state2 << " j: " << j + 1 << " res: " << f[state2][j] << endl;
                    }
                }
            }
        }
    }
    for (int state = 0; state < (1 << n); ++state) {
        if (_count(state) == m) {
            for (int i = 0; i < n; ++i) {
                res = max(res, f[state][i]);
            }
        }
    }
    cout << res << endl;
    return 0;
}