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
    long long subArrayRanges(vector<int> &nums) {
        using ll = long long;
        int n = nums.size();
        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            ll partMax = nums[i], partMin = nums[i];
            for (int j = i + 1; j < n; ++j) {
                partMax = max(partMax, static_cast<ll>(nums[j]));
                partMin = min(partMin, static_cast<ll>(nums[j]));
                sum += partMax - partMin;
            }
        }
        return sum;
    }
};