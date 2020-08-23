void dfs(int n, vector<string> &res, string &strs, int open, int close) {
    if(open < close || open > n || close > n) return;
    if(open == n && close == n) {
        res.push_back(strs);
        return ;
    }
    strs.push_back('(');
    dfs(n, res, strs, open+1, close);
    strs.pop_back();
    strs.push_back(')');
    dfs(n, res, strs, open, close+1);
    strs.pop_back();
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    string strs = "";
    int open = 0, close = 0;
    dfs(n, res, strs, open, close);
    return res;
}