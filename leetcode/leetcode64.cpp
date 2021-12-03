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

int minPathSum(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    int f[n + 1][m + 1];
    f[0][0] = grid[0][0];
    for (int i = 1; i < n; i++) f[i][0] = f[i - 1][0] + grid[i][0];
    for (int i = 1; i < m; i++) f[0][i] = f[0][i - 1] + grid[0][i];
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            f[i][j] = min(f[i][j - 1], f[i - 1][j]) + grid[i][j];
        }
    }
    return f[n - 1][m - 1];
}