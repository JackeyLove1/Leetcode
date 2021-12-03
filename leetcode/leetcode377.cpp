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
    int combinationSum4(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> m;
        function<int(int)> dfs = [&](int cur) -> int {
            if (cur == 0) return 1;
            if (m.count(cur)) return m[cur];
            int &v = m[cur] = 0;
            for (auto &num : nums) {
                if (num <= cur) v += dfs(cur - num);
            }
            return v;
        };
        return dfs(target);
    }
};

int main() {
    vector<int> nums = {1, 2, 3};
    auto s = Solution();
    cout << s.combinationSum4(nums, 4) << endl;
}
