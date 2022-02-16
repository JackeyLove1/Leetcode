#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

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

class Solution_wrong {
public:
    int maximumANDSum(vector<int> &nums, int numSlots) {
        int n = nums.size();
        vector<vector<int>> f((1 << n)+1, vector<int>(numSlots + 1, 0));
        vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = nums[i] & nums[j];
            }
        }
        for (int i = 0; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    for (int s = 1; s < numSlots; ++s) {
                        f[i][s] = max(f[i][s], f[i - (1 << j)][s - 1] + nums[j]);
                    }
                    for (int k = 0; k < n; ++k) {
                        if ((i & (1 << k)) && k != j) {
                            for (int s = 2; s <= numSlots; ++s) {
                                f[i][s] = max(f[i][s], f[i - (1 << k) - (1 << j)][s - 1] + g[k][j]);
                                f[i][s] = max(f[i][s], f[i - (1 << k) - (1 << j)][s - 2] + nums[k] + nums[j]);
                            }
                        }
                    }
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= numSlots; ++i) {
            res = max(res, f[(1 << n) - 1][i]);
        }
        return res;
    }
};

class Solution {
public:
    int maximumANDSum(vector<int> &nums, int s) {
        // 三进制状态压缩
        const int n = nums.size();
        const int m = static_cast<int>(pow(3, s));
        vector<vector<int>> f(n + 1, vector<int>(m, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                int t = j, w = 1;
                // 枚举将第i个数放入第k个篮子中
                for (int k = 1; k <= s; ++k) {
                    if (t % 3) {
                        f[i][j] = max(f[i][j], f[i - 1][j - w] + (k & nums[i - 1]));
                    }
                    // 三进制位操作
                    w *= 3;
                    t /= 3;
                }
            }
        }
        return f[n][m - 1];
    }
};


int main() {
    Solution s;
    vector<int> v1 = {1, 2, 3, 4, 5, 6};
    cout << s.maximumANDSum(v1, 3) << " res: 9" << endl;
    vector<int> v2 = {1, 3, 10, 4, 7, 1};
    cout << s.maximumANDSum(v2, 9) << " res: 24" << endl;
}