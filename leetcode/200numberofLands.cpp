#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

void dfs(vector<vector<char>> &grid, int x, int y) {
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
        return;
    if (grid[x][y] == '0')
        return;
    grid[x][y] = '0';
    // 上下左右遍历
    dfs(grid, x + 1, y);
    dfs(grid, x, y + 1);
    dfs(grid, x - 1, y);
    dfs(grid, x, y - 1);
}

int numIslands(vector<vector<char>> &grid) {
    int cnt = 0;
    if (grid.empty() || grid[0].empty()) return cnt;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                cnt++;
                dfs(grid, i, j);
            }
        }
    }
    return cnt;
}
