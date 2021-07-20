#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>

using namespace std;


void dfs(vector<int>& candidates, int start, int target, vector<int>&path, vector<vector<int>>& res){
    if(start >= candidates.size())
        return ;
    if (target < 0)
        return;
    if(target == 0){
        res.emplace_back(path);
        return ;
    }
    // skip
    dfs(candidates, start+1, target, path, res);
    // choose
    path.push_back(candidates[start]);
    dfs(candidates, start, target - candidates[start], path, res);
    // backTrace
    path.pop_back();
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    int start = 0;
    vector<int> path;
    vector<vector<int>> res;
    dfs(candidates, start, target, path, res);
    return res;
}