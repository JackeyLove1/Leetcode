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
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

#pragma GCC optimize(2)

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
    bool containsNearbyDuplicate(const vector<int> &nums, int k) {
        unordered_map<int, vector<int>> um;
        for (int i = 0; i < nums.size(); ++i) {
            um[nums[i]].push_back(i);
        }
        for (const auto&[_, v] : um) {
            for (int i = 0; i < v.size() - 1; ++i) {
                if (v[i + 1] - v[i] <= k) return true;
            }
        }
        return false;
    }
};