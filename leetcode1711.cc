#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
public:
    int countPairs(vector<int> &deliciousness) {
        using PII = pair<int, int>;
        set<PII> s;
        unordered_map<int, int> cnt;
        for (auto &num : deliciousness) {
            ++cnt[num];
        }
        const int MOD = 1e9 + 7;
        int res = 0;
        int maxNum = *max_element(deliciousness.begin(), deliciousness.end());
        vector<int> ks;
        for (int k = 2; k <= 2 * maxNum; k <<= 1) {
            ks.push_back(k);
        }
        for (auto&[k, cnt1] : cnt) {
            for (auto &k2 : ks) {
                if (cnt.count(k2 - k)) {
                    if (s.count({k, k2 - k})) continue;
                    if (k2 - k == k) {
                        res = (res + cnt1 * (cnt1 - 1) ) % MOD;
                        s.insert({k, k2 - k});
                    } else {
                        int cnt2 = cnt[k2 - k];
                        res = (res + cnt1 * cnt2) % MOD;
                        s.insert({k, k2 - k});
                        s.insert({k2 - k, k});
                    }
                    cout << "k1: " << k << " k2: " << k2 - k << " res: " << res << endl;
                }
            }
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {1, 1, 1, 3, 3, 3, 7};
    // cout << s.countPairs(nums) << " res: 15" << endl;
    vector<int> nums1 = {1, 3, 5, 7, 9};
    // cout << s.countPairs(nums1) << " res:4" << endl;
    vector<int> nums2 = {149, 107, 1, 63, 0, 1, 6867, 1325, 5611, 2581, 39, 89, 46, 18, 12, 20, 22, 234};
    cout << s.countPairs(nums2) << " res:12" << endl;
    return 0;
}