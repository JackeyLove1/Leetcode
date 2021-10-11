// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

class Solution {
public:
    int maximumUniqueSubarray(vector<int> &nums) {
        int n = nums.size();
        int res = INT_MIN;
        int l = 0, r = 0, sum = 0;
        unordered_map<int, int> m;
        for (; r < n; ++r) {
            ++m[nums[r]];
            sum += nums[r];
            while (l < r && m[nums[r]] > 1) {
                --m[nums[l]];
                sum -= nums[l];
                ++l;
            }
            res = max(res, sum);
        }
        return res;
    }
};