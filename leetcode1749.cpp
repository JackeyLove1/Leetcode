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
    int maxAbsoluteSum(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> f(n + 2, 0), g(n + 2, 0);
        int res = 0;
        f[0] = g[0] = nums[0];
        res = max(res, abs(nums[0]));
        for (int i = 1; i < n; ++i) {
            f[i] = max(f[i - 1] + nums[i], nums[i]);
            g[i] = min(g[i - 1] + nums[i], nums[i]);
            res = max(res, max(abs(f[i]), abs(g[i])));
        }
        return res;
    }
};