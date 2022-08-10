#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e6 + 1000;
// int n, k;

class Solution {
public:
    bool validPartition(vector<int> &nums) {
        // sort(nums.begin(), nums.end());
        const int n = nums.size();
        bool f[n + 1];
        memset(f, 0, sizeof f);
        f[0] = true;
        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1]) {
                f[i + 1] = f[i + 1] || f[i - 1];
            }
            if (i >= 2) {
                if (nums[i] == nums[i - 1] && nums[i - 1] == nums[i - 2]) {
                    f[i + 1] = f[i + 1] || f[i - 2];
                } else if (nums[i] == nums[i - 1] + 1 && nums[i - 1] == nums[i - 2] + 1) {
                    f[i + 1] = f[i + 1] || f[i - 2];
                }
            }
        }
        return f[n];
    }
};

int main() {
    Solution s;
    vector<int> nums1 = {993335, 993336, 993337, 993338, 993339, 993340, 993341};
    cout << s.validPartition(nums1) << " expect: 0" << endl;
    vector<int> nums2 = {4, 4, 4, 5, 6};
    cout << s.validPartition(nums2) << " expect: 1" << endl;
    vector<int> nums3 = {803201, 803201, 803201, 803201, 803202, 803203};
    cout << s.validPartition(nums3) << " expect: 1" << endl;
    return 0;
}