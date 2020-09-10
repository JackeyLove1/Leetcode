#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;

void
deepSearch(vector<int> &candidates, int target, int start, vector<int> &path, unordered_map<vector<int>, int> &hash,
           vector<vector<int>> &res) {
    if (target < 0 || start >= candidates.size())
        return;
    if (target == 0 && hash.find(path) == hash.end()) {
        hash[path] = 1;
        res.emplace_back(path);
        return;
    }
    for (int i = start; i < candidates.size(); i++) {
        path.push_back(candidates[i]);
        deepSearch(candidates, target - candidates[i], i + 1, path, hash, res);
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    int start = 0;
    vector<int> path;
    vector<vector<int>> res;
    unordered_map<vector<int>, int> hash;
    sort(candidates.begin(), candidates.end());
    deepSearch(candidates, target, start, path, hash, res);
    return res;
}

void print(vector<vector<int>> &res) {
    for (auto nums : res) {
        for (auto num : nums) {
            cout << num << "  ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    vector<vector<int>> res = combinationSum2(candidates, 8);
    print(res);
}