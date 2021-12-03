#include <iostream>
#include <vector>

using namespace std;

// vector<vector<int>> path;

int helper(int x, int y, vector<vector<int>> &path) {
    if (path[x][y] > 0)
        return path[x][y];
    if (x < 1 || y < 1) {
        path[x][y] = 0;
        return path[x][y];
    }
    if (x == 1 && y == 1) {
        path[x][y] = 1;
        return path[x][y];
    }
    path[x][y] = helper(x - 1, y, path) + helper(x, y - 1, path);
    return path[x][y];
}

int uniquePaths(int m, int n) {
    // hash
    vector<vector<int>> path(m + 1, vector<int>(n + 1, 0));
    return helper(m, n, path);
}

int main() {
    cout << uniquePaths(3, 2) << endl;
    cout << uniquePaths(7, 3) << endl;
    return 0;
}