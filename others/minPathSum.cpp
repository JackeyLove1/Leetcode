#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

int minPathSum(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int f[m][n];
    f[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) {
        f[i][0] = f[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < n; j++) {
        f[0][j] = f[0][j - 1] + grid[0][j];
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = grid[i][j] + min(f[i - 1][j], f[i][j - 1]);
        }
    }
    return f[m - 1][n - 1];
}