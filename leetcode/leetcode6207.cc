#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <numeric>
#include <cmath>


using namespace std;
using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;


class Solution {
public:
    long long countSubarrays(vector<int> &nums, int minK, int maxK) {
        if (maxK > minK) return 0;
        set<int> smin, smax;
        set<int> mid, dismid;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == minK) smin.insert(i);
            if (nums[i] == maxK) smax.insert(i);
            if (nums[i] >= minK && nums[i] <= maxK) mid.insert(i);
            if (minK > nums[i] || maxK > nums[i]) dismid.insert(i);
        }
        long res = 0;
        const auto n = nums.size() - 1;
        for (auto v: mid) {
            auto iter1 = smin.lower_bound(v);
            if (iter1 == smin.end()) continue;
            auto iter2 = smax.lower_bound(v);
            if (iter2 == smax.end()) continue;
            auto end1 = std::max(*iter1, *iter2);
            auto iter3 = dismid.upper_bound(v);
            if (iter3 != dismid.end()) {
                auto end2 = *iter3;
                if (end2 <= end1) continue;
                else res += end2 - 1 - v;
            } else {
                res += n - v;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums{1, 3, 5, 2, 7, 5};
    cout << s.countSubarrays(nums, 1, 5) << " res: 2" << endl;
    return 0;
}