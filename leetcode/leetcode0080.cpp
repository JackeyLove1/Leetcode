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
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums(n, 0);
        std::iota(nums.begin(), nums.end(), 1);
        vector<vector<int>> res;
        // print(nums);
        for (int s = 0; s < (1 << n); ++s) {
            if (count(s) == k) {
                vector<int> tmp;
                tmp.reserve(k);
                for (int i = 0; i < n; ++i) {
                    if (s & (1 << i)) {
                        tmp.push_back(nums[i]);
                    }
                }
                res.emplace_back(tmp);
            }
        }
        return res;
    }
};

