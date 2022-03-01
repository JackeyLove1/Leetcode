#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>
#include <stack>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int _count(int x) {
    return __builtin_popcount(x);
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

constexpr int N = 110, M = 1 << 10, INF = 0x3f3f3f3f;
int g[N], cnt[M];
int f[2][M][M];
vector<int> state;
vector<int> head[M];
int n, m;

inline bool check(int state) {
    return !((state & (state >> 1)) || (state & (state >> 2)));
}


int main() {
    fhj();
    cin >> n >> m;
    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c;
            g[i] += (c == 'H') << j;
        }
    }

    for (int s = 0; s < (1 << m); ++s) {
        if (check(s)) {
            state.push_back(s);
            cnt[s] = _count(s);
        }
    }

    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state.size(); ++j) {
            if (i == j) continue;
            auto state_i = state[i];
            if (!(state_i & state[j])) {
                head[state_i].push_back(state[j]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < state.size(); ++j) {
            for (int k = 0; k < state.size(); ++k) {
                for (int u = 0; u < state.size(); ++u) {
                    int a = state[j], b = state[k], c = state[u];
                    if ((a & b) || (a & c) || (b & c)) continue;
                    if ((g[i] & b) || (g[i - 1] & a)) continue;
                    f[i & 1][j][k] = max(f[i & 1][j][k], f[i - 1 & 1][u][j] + cnt[b]);
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state.size(); ++j) {
            res = max(res, f[n & 1][i][j]);
        }
    }
    cout << res << endl;
    return 0;
}