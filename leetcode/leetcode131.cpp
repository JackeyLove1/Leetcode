#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

using namespace std;

inline bool judge(string &s) {
    if (s.size() == 1) return true;
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

void dfs(string &s, vector<vector<string>> &res, vector<string> &path, int idx) {
    if (idx >= s.size()) {
        res.emplace_back(path);
        return;
    }
    for (int i = idx; i < s.size(); i++) {
        string tmp = s.substr(idx, i - idx + 1);
        if (judge(tmp)) {
            path.emplace_back(tmp);
            dfs(s, res, path, i + 1);
            path.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> path;
    int idx = 0;
    dfs(s, res, path, idx);
    return res;
}