#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending .... " << endl;
}

void
dfs(vector<int> &candidates, int start, int target, vector<int> &path, vector<vector<int>> &res, set<vector<int>> &s) {
    if (target < 0)
        return;
    if (target == 0) {
        if (!s.count(path)) {
            s.insert(path);
            res.emplace_back(path);
        }
        return;
    }
    if (start >= candidates.size())
        return;
    // skip
    dfs(candidates, start + 1, target, path, res, s);
    // choose
    path.push_back(candidates[start]);
    // cout << "can: "<< candidates[start] << endl;
    dfs(candidates, start + 1, target - candidates[start], path, res, s);
    // backTrace
    path.pop_back();
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    set<vector<int>> s;
    int start = 0;
    vector<int> path;
    vector<vector<int>> res;
    dfs(candidates, start, target, path, res, s);
    return res;
}

int main() {
    vector<int> candidates = {2, 5,2,1,2};
    int target = 5;
    auto res = combinationSum2(candidates, target);
    print(res);
}