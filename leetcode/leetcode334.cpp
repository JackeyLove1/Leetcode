#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    bool increasingTriplet(vector<int> &nums) {
        if (nums.size() < 3) return false;
        // dp, 悬垂线问题
        // 开两个数组，一个保存左边的最小值，一个保存右边最大值
        vector<int> left(nums.size() + 2, nums.front());
        vector<int> right(nums.size() + 2, nums.back());
        for (int i = 1; i <= nums.size(); ++i) {
            left[i] = min(left[i - 1], nums[i - 1]);
        }
        for (int i = nums.size() - 2; i >= 0; --i) {
            right[i] = max(right[i + 1], nums[i + 1]);
        }
        // print(left);
        // print(right);
        for (int i = 0; i < nums.size(); ++i) {
            if (left[i] < nums[i] && nums[i] < right[i]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {20, 100, 10, 12, 5, 13};
    cout << s.increasingTriplet(v1) << " res: 1" << endl;
}