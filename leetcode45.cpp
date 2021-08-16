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
    unordered_map<int, int> cache;
    static constexpr int INF = 1e9;
public:
    int solve(vector<int> &nums, int curIndex, int curStep) {
        if (cache.count(curIndex)) return cache[curIndex];
        cache[curIndex] = INF;
        int &v = cache[curIndex];
        if (curIndex >= nums.size() - 1) {
            return v = curStep;
        }
        for (int i = 1; i <= nums[curIndex]; i++) {
            v = min(v, 1 + solve(nums, curIndex + i, 0));
        }
        return v;
    }

    int jump(vector<int> &nums) {
        cache.clear();
        return solve(nums, 0, 0);
    }
};

int main() {
    vector<int> nums = {2, 3, 1, 1, 4};
    auto s = Solution();
    cout << s.jump(nums) << " res: 2" << endl;
    vector<int> nums1 = {2, 3, 0, 1, 4};
    cout << s.jump(nums1) << " res: 2" << endl;
    return 0;
}