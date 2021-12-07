#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int minimumDifference(vector<int> &nums, int k) {
        if (k == 1) return 0;
        sort(nums.begin(), nums.end());
        int l = 0, r = k - 1;
        int res = nums[r] - nums[l];
        for (; r < nums.size(); ++l, ++r) {
            res = min(res, nums[r] - nums[l]);
        }
        return res;
    }
};