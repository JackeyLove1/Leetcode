#include <iostream>
// #include "Logger.h"

using namespace std;

#include <unordered_map>
#include <vector>

class Solution {
public:
    int numSubarraysWithSum(vector<int> &nums, int goal) {
        // 计算记录前缀和
        // 再使用map寻找
        int preSum = 0, res = 0;
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < nums.size(); ++i) {
            m[preSum].push_back(i);
            preSum += nums[i];
            if (m.count(preSum - goal)) {
                res += m[preSum - goal].size();
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {0, 0, 0, 0, 0};
    Solution s;
    cout << s.numSubarraysWithSum(nums, 0) << " res: 15" << endl;
}