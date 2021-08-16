#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
private:
    using PII = pair<int, int>;
    unordered_map<int, int> m;
    map<PII, bool> cache;
    vector<int> nums;
    int n;
public:
    bool solve(int cur, int k) {
        if (cur == n - 1) return true; // 到达最后一块石头
        if (cache.find({cur, k}) != cache.end()) {
            return cache[{cur, k}];
        }
        cache[{cur, k}] = false;
        bool &b = cache[{cur, k}];
        for (int i = -1; i <= 1; i++) {
            if (k + i == 0) continue; // 原地踏步
            int next = nums[cur] + k + i;
            if (m.count(next)) {
                // 存在则跳转到下一步
                // cout << "m[next]: " << m[next] << endl;
                bool forward = solve(m[next], k + i);
                if (forward) return b = forward;
            }
        }
        return b = false;
    }

    bool canCross(vector<int> &stones) {
        n = stones.size();
        for (int i = 0; i < n; i++) {
            m[stones[i]] = i; // 高度 --> 下标
        }
        if (!m.count(1)) return false;
        nums = move(stones);
        return solve(1, 1);
    }
};

int main() {
    vector<int> nums = {0, 1, 3, 5, 6, 8, 12, 17};
    auto s = Solution();
    // cout << s.canCross(nums) << " res: 1" << endl;
    vector<int> nums2 = {0, 1, 2, 3, 4, 8, 9, 11};
    cout << s.canCross(nums2) << " res: 0" << endl;
    return 0;
}