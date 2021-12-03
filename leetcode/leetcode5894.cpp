// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
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
    vector<int> twoOutOfThree(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3) {
        vector<int> ans;
        unordered_set<int> s1, s2, s3;
        unordered_map<int, int> cnt;
        for (auto &num : nums1) {
            if (!s1.count(num)) {
                s1.insert(num);
                ++cnt[num];
            }
        }
        for (auto &num : nums2) {
            if (!s2.count(num)) {
                s2.insert(num);
                ++cnt[num];
            }
        }
        for (auto &num : nums3) {
            if (!s3.count(num)) {
                s3.insert(num);
                ++cnt[num];
            }
        }
        for (auto&[k, v] : cnt) {
            if (v > 1) ans.push_back(k);
        }
        return ans;
    }
};