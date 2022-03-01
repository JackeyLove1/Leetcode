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

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 18, INF = 0x3f3f3f3f;
using ll = long long;
int f[N + 2][1 << N];
int nums[N];
int n, m;


int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++i) {
        f[1][1 << i] = nums[i];
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            if (f[i][j] != INF) {// 状态有效
                for (int k = 0; k < n; ++k) {
                    if (j & (1 << k)) continue;
                    if (f[i][j] + nums[k] <= m) {
                        // 状态允许, 加入这个状态的最小路径
                        f[i][j | (1 << k)] = min(f[i][j | (1 << k)], f[i][j] + nums[k]);
                    } else {
                        f[i + 1][j | (1 << k)] = min(f[i][j | (1 << k)], nums[k]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (f[i][(1 << n) - 1] != INF) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}