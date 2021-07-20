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
dfs(vector<int> &candidates, int start, int target, vector<int> &path, vector<vector<int>> &res, int k) {
    if (target < 0 || path.size() > k)
        return;
    if (target == 0 && path.size() == k) {

        res.emplace_back(path);

        return;
    }
    if (start >= candidates.size())
        return;
    // skip
    dfs(candidates, start + 1, target, path, res, k);
    // choose
    path.push_back(candidates[start]);
    // cout << "can: "<< candidates[start] << endl;
    dfs(candidates, start + 1, target - candidates[start], path, res, k);
    // backTrace
    path.pop_back();
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int start = 0, target = n;
    vector<vector<int>> res;
    vector<int> path;
    dfs(candidates, start, target, path, res, k);
    return res;
}