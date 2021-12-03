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

void dfs(vector<string> &res, string &path, int left, int right, int n) {
    if (left > n || right > n || right > left) return;
    if (left == n && right == n) {
        // cout << "path: " << path << endl;
        res.push_back(path);
        return;
    }
    // cout << "path: " << path << endl;
    path.push_back('(');
    dfs(res, path, left + 1, right, n);
    path.pop_back();
    path.push_back(')');
    dfs(res, path, left, right + 1, n);
    path.pop_back();
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    string path;
    int left = 0, right = 0;
    dfs(res, path, left, right, n);
    return res;
}

int main() {
    auto res1 = generateParenthesis(3);
    print(res1);
    auto res2 = generateParenthesis(1);
    print(res2);
    return 0;
}