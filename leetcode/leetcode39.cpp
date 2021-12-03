#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

void dfs(vector<int> &candidates, int start, int target, vector<int> &path, vector<vector<int>> &res) {
    if (start >= candidates.size())
        return;
    if (target < 0)
        return;
    if (target == 0) {
        res.push_back(path);
        return;
    }
    // skip
    dfs(candidates, start + 1, target, path, res);
    // chose
    path.push_back(candidates[start]);
    dfs(candidates, start , target-candidates[start], path, res);
    path.pop_back();
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    int start = 0;
    vector<int> path;
    vector<vector<int>> res;
    dfs(candidates, start, target, path, res);
    return res;
}

void print(vector<vector<int>> res) {
    for (auto vec : res) {
        for (auto v : vec) {
            cout << v << "  ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> res = combinationSum(candidates, target);
    print(res);
}