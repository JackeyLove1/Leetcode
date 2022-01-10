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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 55;
int g[N][N];
int f[N * 2 + 10][N][N];
int m, n;

int main() {
    fhj();
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> g[i][j];
        }
    }
    for (int k = 2; k <= m + n; ++k) {
        for (int i = 1; i <= m && i < k; ++i) {
            for (int j = 1; j <= n && j < k; ++j) {
                int &v = f[k][i][j];
                int tmp = g[i][k - i];
                if (i != j) {
                    tmp += g[j][k - j];
                }
                v = max({v, f[k - 1][i][j], f[k - 1][i - 1][j],
                         f[k - 1][i][j - 1], f[k - 1][i - 1][j - 1]});
                v += tmp;
            }
        }
    }
    cout << f[m + n][m][n] << endl;
    return 0;
}