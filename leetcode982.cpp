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
    int countTriplets(vector<int> &nums) {
        constexpr int N = 1 << 16;
        vector<int> f(N, 0);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                auto state = nums[i] & nums[j];
                ++f[state];
            }
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            int state = N - 1 - nums[i]; // 找到合法状态母集
            // 枚举子集, 本质是不断去掉末尾的1
            for (int j = state; j; j = (j - 1) & state) {
                res += f[j];
            }
            res += f[0]; // 不要忘记万能兼容集合
        }
        return res;
    }
};