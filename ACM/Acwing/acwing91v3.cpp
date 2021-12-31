// Author: Jacky
// Time: 2021-09-17
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


int n;
constexpr int N = 21;
int g[N][N];
int f[1 << 20][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    f[1][0] = 0;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                for (int k = 0; k < n; ++k) {
                    if ((i & (1 << k))) {
                        f[i][j] = min(f[i - (1 << j)][k] + g[k][j], f[i][j]);
                    }
                }
            }
        }
    }
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}