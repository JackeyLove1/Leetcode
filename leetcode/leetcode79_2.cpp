#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void dfs(int x, int y, vector<vector<char>> &board, vector<vector<bool>> &visited, string &word, int start, int &flag) {
    if (start >= word.size()) {
        flag = 1;
        return;
    }
    if (x >= visited.size() || x < 0 || y >= visited[0].size() || y < 0)
        return;
    if (visited[x][y] || board[x][y] != word[start])
        return;
    visited[x][y] = true;
    dfs(x + 1, y, board, visited, word, start + 1, flag);
    dfs(x - 1, y, board, visited, word, start + 1, flag);
    dfs(x, y + 1, board, visited, word, start + 1, flag);
    dfs(x, y - 1, board, visited, word, start + 1, flag);
    visited[x][y] = false;
}

bool exist(vector<vector<char>> &board, string word) {
    if (board.empty() || board[0].empty())
        return false;
    int m = board.size(), n = board[0].size();
    // use backtrace method

    // 1. find the start point
    deque<pair<int, int>> d;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0])
                d.push_back(pair<int, int>(i, j));
        }
    }

    // 2. use dfs to solve the problem
    while (!d.empty()) {
        auto tmp = d.front();
        d.pop_front();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int start = 0, flag = 0;
        dfs(tmp.first, tmp.second, board, visited, word, start, flag);
        if (flag)
            return true;
    }
    return false;
}