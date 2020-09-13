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

bool dfs(int x, int y, vector<vector<char> > &board, vector<vector<bool> > &visited, string &word, int start) {
    if (start >= word.size()) {
        return true;
    }
    if (x >= visited.size() || x < 0 || y >= visited[0].size() || y < 0)
        return false;
    if (!visited[x][y] && board[x][y] == word[start]) {
        visited[x][y] = true;
        bool flag = dfs(x + 1, y, board, visited, word, start + 1) ||
                    dfs(x - 1, y, board, visited, word, start + 1) ||
                    dfs(x, y + 1, board, visited, word, start + 1) ||
                    dfs(x, y - 1, board, visited, word, start + 1);
        if (flag) return true;
        visited[x][y] = false;
    }
    return false;
}

bool exist(vector<vector<char> > &board, string word) {
    if (board.empty() || board[0].empty())
        return false;
    int m = board.size(), n = board[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int start = 0;
            if (dfs(i, j, board, visited, word, start))
                return true;
        }
    }
    return false;
}