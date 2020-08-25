set<vector<int>> s;

void dfs(vector<vector<int>> &res, vector<int> &tmp, vector<int> &nums, int start) {
    if (tmp.size() > 1 && s.find(tmp) == s.end()) {
        s.insert(tmp);
        res.push_back(tmp);
    }
    for (int i = start; i < nums.size(); i++) {
        if(tmp.empty() || tmp.back() <= nums[i]){
            tmp.push_back(nums[i]);
            dfs(res, tmp, nums, i+1);
            tmp.pop_back();
        }
    }
}

vector<vector<int>> findSubsequences(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> tmp;
    int start = 0;
    dfs(res, tmp, nums, start);
    return res;
}