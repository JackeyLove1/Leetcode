#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix) {
    vector<int> res;
    if (matrix.empty()) return res;
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    int x = 0, y = 0, count = 0;
    while (count < m * n) {
        if (!visited[x][y]) {
            visited[x][y] = true;
            res.push_back(matrix[x][y]);
            count++;
            continue;
        }
        // to right
        while (y + 1 < n && !visited[x][y + 1]) {
            visited[x][++y] = true;
            res.push_back(matrix[x][y]);
            count++;
            continue;
        }
        // to bottom
        while (x + 1 < m && !visited[x + 1][y]) {
            visited[++x][y] = true;
            res.push_back(matrix[x][y]);
            count++;
            continue;
        }
        // to left
        while (y - 1 >= 0 && !visited[x][y - 1]) {
            visited[x][--y] = true;
            res.push_back(matrix[x][y]);
            count++;
            continue;
        }
        // to top
        while (x - 1 >= 0 && !visited[x - 1][y]) {
            visited[--x][y] = true;
            res.push_back(matrix[x][y]);
            count++;
            continue;
        }
    }
    return res;
}