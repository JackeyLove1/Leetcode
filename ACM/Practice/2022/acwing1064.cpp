#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int cnt(int x) {
    return __builtin_popcount(x);
}

static constexpr int N = 12, M = 1 << 10, K = 110;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1e7 + 7;
using ll = long long;

ll f[N][K][M];
int n, m;

vector<int> states;
vector<int> heads[M];
int id[M];

inline bool check(int state) {
    return !(state & (state << 1));
}

int main() {
    fhj();
    cin >> n >> m;
    int max_mask = 1 << n;
    for (int i = 0; i < max_mask; ++i) {
        if (check(i)) {
            states.push_back(i);
            id[i] = cnt(i);
        }
    }

    for (const auto a : states) {
        for (const auto b : states) {
            if (!(a & b) && check(a | b)) {
                heads[a].push_back(b);
            }
        }
    }

    f[0][0][0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (const auto a : states) {
                auto c = id[a];
                if (j >= c) {
                    for (const auto b : heads[a]) {
                        f[i][j][a] += f[i - 1][j - c][b];
                    }
                }
            }
        }
    }

    cout << f[n + 1][m][0] << endl;
    return 0;
}