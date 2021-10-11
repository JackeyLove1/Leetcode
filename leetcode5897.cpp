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

class SolutionW {
public:
    int minimumDifference(vector<int> &nums) {
        int n = nums.size();
        int half = n / 2;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int res = INT_MAX;
        for (int i = 0; i < (1 << n); ++i) {
            if (__builtin_popcount(i) != half) continue;
            int k = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    k += nums[j];
                }
            }
            res = min(res, abs(2 * k - sum));
        }
        return res;
    }
};



class Solution {
public:
    int minimumDifference(vector<int> &nums) {
        int n = nums.size();
        int m = n / 2;
        vector<vector<int>> f(n + 1), g(n + 1);
        for (int mask = 0; mask < (1 << m); ++mask) {
            int sum = 0;
            int cnt = __builtin_popcount(mask);
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                } else {
                    sum -= nums[i];
                }
            }
            f[cnt].push_back(sum);
        }
        for (int mask = 0; mask < (1 << m); ++mask) {
            int sum = 0;
            int cnt = __builtin_popcount(mask);
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    sum += nums[i + m];
                } else {
                    sum -= nums[i + m];
                }
            }
            g[cnt].push_back(sum);
        }
        for (int i = 0; i < n; ++i) {
            sort(f[i].begin(), f[i].end());
            sort(g[i].begin(), g[i].end());
        }
        int res = INT_MAX;
        for (int i = 0; i <= m; ++i) {
            for (auto &num : f[i]) {
                auto it = lower_bound(g[m - i].begin(), g[m - i].end(), -num);
                if (it != g[m - i].end()) {
                    res = min(res, abs(num + *it));
                }
                if (it != g[m - i].begin()) {
                    res = min(res, abs(num + *prev(it)));
                }
            }
        }
        return res;
    }
};

