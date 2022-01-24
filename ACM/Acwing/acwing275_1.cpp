#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

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

constexpr int maxn = 55;

int mat[maxn][maxn];
int f[maxn << 1][maxn][maxn];

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> mat[i][j];

    for (int k = 2; k <= n + m; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = 1; j < k; j++) {
                int t = mat[i][k - i];
                if (i != j) {
                    t += mat[j][k - j];
                }
                f[k][i][j] = t + max({f[k - 1][i][j],
                                      f[k - 1][i - 1][j],
                                      f[k - 1][i][j - 1],
                                      f[k - 1][i - 1][j - 1]});
            }
        }
    }

    cout << f[n + m][n][n] << endl;
    return 0;
}