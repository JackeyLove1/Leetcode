#include <iostream>
#include <vector>

using namespace std;

int dfs(int x, int y, vector<vector<int>> &obstacleGrid) {
    if (x < 0 || y < 0) return 0;
    if (x == 0 && y == 0) {
        return 1;
    }
    if (obstacleGrid[x][y] == 1) return 0;
    return dfs(x - 1, y, obstacleGrid) + dfs(x, y - 1, obstacleGrid);
}

int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    if(obstacleGrid[0][0] == 1) return 0;
    int res = 0;
    return dfs(m - 1, n - 1, obstacleGrid);
}

int main() {
    vector<vector<int>> obstacleGrid = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
    };
    cout << uniquePathsWithObstacles(obstacleGrid) << endl;
    return 0;
}