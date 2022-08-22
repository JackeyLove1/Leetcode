#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

class Solution {
    int nums[26];

    int solve(const string &s) {
        memset(nums, 0, sizeof nums);
        int cursum = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (++nums[s[i] - 'a'] < i + 1) {
                int maxn = *max_element(nums, nums + 26);
                int minn = max(1, *min_element(nums, nums + 26));
                cursum += maxn - minn;
                // cout <<"cursum: " << cursum << endl;
            }
        }
        return cursum;
    }

public:
    int beautySum(string s) {
        int summ = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto sub = s.substr(0, i + 1);
            reverse(sub.begin(), sub.end());
            summ += solve(sub);
        }
        return summ;
    }
};

int main() {
    Solution s{};
    cout << s.beautySum("aabcb") << " res: 5" << endl;
    cout << s.beautySum("aabcbaa") << " res: 17" << endl;
}