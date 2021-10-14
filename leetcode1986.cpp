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
    int minSessions(vector<int> &tasks, int sessionTime) {
        // 状态压缩DP
        int n = tasks.size();
        vector<int> f(1 << n, 15);
        vector<int> cost(1 << n, 20);
        f[0] = 0;
        for (int i = 0; i < 1 << n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    if (sessionTime >= cost[i - (1 << j)] + tasks[j]) {
                        cost[i] = min(cost[i], cost[i - (1 << j)] + tasks[j]);
                        f[i] = min(f[i], f[i - (1 << j)]);
                    } else {
                        cost[i] = min(cost[i], tasks[j]);
                        f[i] = min(f[i], f[i - (1 << j)] + 1);
                    }
                }
            }
        }
        return f[(1 << n) - 1];
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {2, 3, 3, 4, 4, 4, 5, 6, 7, 10};
    cout << s.minSessions(nums, 12) << endl;
}