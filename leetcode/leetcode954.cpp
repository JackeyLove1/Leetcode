#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
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
    bool canReorderDoubled(vector<int> &arr) {
        // if (arr.size() < 4) return false;
        int target_size = arr.size() / 2;
        unordered_map<int, int> um;
        for (const int num : arr) {
            ++um[num];
        }
        int sz = 0;
        sort(arr.begin(), arr.end());
        for (const auto num : arr) {
            if (num == 0 && um[num] > 0) {
                if (um[num] % 2 == 1) --um[num];
                sz += um[num] / 2;
                um[num] = 0;
                continue;
            }
            if (um[num] > 0 && um[num * 2] > 0) {
                um[num]--, um[num * 2]--;
                sz++;
            }
        }
        // cout << sz << endl;
        return sz >= target_size;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {2, 4, 0, 0, 8, 1};
    cout << s.canReorderDoubled(nums0) << " res: 1" << endl;
    vector<int> nums1 = {0, 0};
    cout << s.canReorderDoubled(nums1) << " res: 1" << endl;
    vector<int> nums2 = {-33, 0};
    cout << s.canReorderDoubled(nums2) << " res: 0" << endl;
}
