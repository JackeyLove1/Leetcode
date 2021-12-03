void dfs(vector<int> &nums, vector<bool> visited, vector<vector<int>> &res, vector<int> &tmp, set<vector<int>> &s,
         int start) {
    if (tmp.size() > 1 && s.find(tmp) == s.end()) {
        res.push_back(tmp);
        s.insert(tmp);
    }
    for (int i = start; i < nums.size(); i++) {
        if(!visited[i]){
            if(tmp.empty() || tmp.back() <= nums[i]){
                visited[i] = true;
                tmp.push_back(nums[i]);
                dfs(nums, visited,res,tmp,s,i+1);
                visited[i] = false;
                tmp.pop_back();
            }
        }
    }
}

vector<vector<int>> findSubsequences(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> tmp;
    set<vector<int>> s;
    vector<bool> visited(nums.size(), false);
    dfs(nums,visited, res, tmp, s, 0);
    return res;
}