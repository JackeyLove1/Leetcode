#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    using PII = pair<int, int>;
    map<PII, int> cache;
public:
    int dfs(vector<int> &nums, int target, int cur, int partSum) {
        int n = nums.size();
        PII p = {cur, partSum};
        if (cache.find(p) != cache.end()) return cache[p];
        cache[p] = 0;
        int &v = cache[p];
        if (cur == n) {
            if (target == partSum) {
                // count++;
                return v = 1;
            }
            return v; // end dfs
        }
        int left = dfs(nums, target, cur + 1, partSum + nums[cur]);
        int right = dfs(nums, target, cur + 1, partSum - nums[cur]);
        return v = left + right;
    }

    int findTargetSumWays(vector<int> &nums, int target) {
        cache.clear();
        return dfs(nums, target, 0, 0);
    }
};

int main() {
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    auto s = Solution();
    cout << s.findTargetSumWays(nums, target) << endl;
    vector<int> nums1 = {1};
    int target1 = 1;
    cout << s.findTargetSumWays(nums1, target1) << endl;
    return 0;
}