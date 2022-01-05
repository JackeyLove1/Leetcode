#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
        std::function<void(int, int, vector<int> &)> dfs = [&](int cur, int sum, vector<int> &path) {
            if (sum == target) {
                res.push_back(path);
                return;
            }
            if (cur >= candidates.size() || sum > target) return;
            for (int i = cur; i < candidates.size(); ++i) {
                path.push_back(candidates[i]);
                dfs(i, sum + candidates[i], path);
                path.pop_back();
            }
        };
        vector<int> path;
        dfs(0, 0, path);
        return res;
    }
};