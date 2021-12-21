#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int maxAscendingSum(vector<int> &nums) {
        int n = nums.size();
        vector<int> f(n + 1, 0);
        int res = -1e9;
        for (int i = 0; i < n; ++i) {
            f[i] = nums[i];
            int prev = nums[i];
            for (int j = i + 1; j < n; ++j) {
                if (nums[j] > prev) {
                    f[i] += nums[j];
                    prev = nums[j];
                    continue;
                }
                break;
            }
            res = max(res, f[i]);
        }
        return res;
    }
};