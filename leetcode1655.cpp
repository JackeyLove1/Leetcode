#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cstring>

using namespace std;

class Solution {
public:
    bool canDistribute(vector<int> &nums, vector<int> &quantity) {
        vector<int> cnt;
        unordered_map<int, int> um;
        for (auto &num : nums) {
            ++um[num];
        }
        for (auto&[_, v] : um) {
            cnt.push_back(v);
        }
        int n = cnt.size(), m = quantity.size();
        // 状态state全都用i的话需要多少cnt[i]
        vector<int> sum(1 << m, 0);
        for (int state = 0; state < 1 << m; state++) {
            for (int j = 0; j < m; j++) {
                if (state & (1 << j)) {
                    auto left = state - (1 << j);
                    sum[state] = sum[left] + quantity[j];
                }
            }
        }

        vector<vector<bool>> f(n, vector<bool>(1 << m, false));
        for (int i = 0; i < n; i++) f[i][0] = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 1 << m; j++) {
                if (i > 0 && f[i - 1][j]) {
                    f[i][j] = true;
                    continue;
                }
                // 枚举子状态
                for (int s = j; s; s = ((s - 1) & j)) {
                    int prev = j - s;
                    bool last = (i == 0) ? (prev == 0) : f[i - 1][prev];
                    bool cur = sum[s] <= cnt[i];
                    if (last && cur) {
                        f[i][j] = true;
                        break;
                    }
                }
            }
        }
        return f[n - 1][(1 << m) - 1];
    }
};