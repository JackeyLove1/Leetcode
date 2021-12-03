#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
    const int debug = 1;
public:
    int shortestSubarray(vector<int> &nums, int k) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        map<int, vector<int>> m;
        m[0].push_back(0);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + nums[i];
            m[sum[i + 1]].push_back(i + 1);
        }
        if (debug) {
            print(sum);
            for (auto&[k1, v]: m) {
                cout << "k: " << k1 << " v: ";
                print(v);
            }
        }
        int res = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            int target = sum[i - 1] + k;
            auto it = m.lower_bound(target);
            if (it != m.end()) {
                auto v = it->second;
                if (debug) {
                    cout << "pos: " << i - 1 << " find target: " << it->first << " v: ";
                    print(v);
                }
                auto it2 = lower_bound(v.begin(), v.end(), i - 1);
                if (it2 != v.end()) res = min(res, (*it2) - i + 1);
            }
        }
        return res == INT_MAX ? -1 : res;
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {2, -1, 2};
    cout << s.shortestSubarray(nums, 3) << " res:3" << endl;
    vector<int> nums1 = {1};
    cout << s.shortestSubarray(nums1, 1) << " res: 1" << endl;
    vector<int> nums2 = {1, 2};
    cout << s.shortestSubarray(nums2, 4) << " res: -1" << endl;
    vector<int> nums3 = {56, -21, 56, 35, -9};
    cout << s.shortestSubarray(nums3, 61) << " res: 2" << endl;
    return 0;
}