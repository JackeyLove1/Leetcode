#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// using recursion
vector<vector<string>> res;

bool isPalindrom(string s) {
    int n = s.size();
    if (n == 1) return true;
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1])
            return false;
    }
    return true;
}

void backtrack(string &s, vector<string> &path, int pre) {
    if (pre >= s.size()) {
        res.push_back(path);
        return;
    }
    for (int i = pre; i < s.size(); i++) {
        string tmp = s.substr(pre, i - pre + 1);
        if (!isPalindrom(tmp))
            continue;
        else {
            path.push_back(tmp);
            backtrack(s, path, i + 1);
            path.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<string> path;
    backtrack(s, path, 0);
    return res;
}

int main() {
    string s = "aab";
    partition(s);
    for (auto strs : res) {
        for (auto str : strs) {
            cout << str << " ";
        }
        cout << endl;
    }
    return true;
}