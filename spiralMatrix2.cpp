#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<vector<int>> generateMatrix(int n) {
    if (n == 0) return {{}};
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<int>> matrix(n, vector<int>(n,0));
    int x = 0, y = 0, count = 1;
    while (count <= n * n) {
        if (!visited[x][y]) {
            visited[x][y] = true;
            matrix[x][y] = count;
            count++;
            continue;
        }
        // to right
        while (y + 1 < n && !visited[x][y + 1]) {
            visited[x][++y] = true;
            matrix[x][y] = count;
            count++;
        }
        // to bottom
        while (x + 1 < n && !visited[x + 1][y]) {
            visited[++x][y] = true;
            matrix[x][y] = count;
            count++;
        }
        // to left
        while (y - 1 >= 0 && !visited[x][y - 1]) {
            visited[x][--y] = true;
            matrix[x][y] = count;
            count++;
        }
        // to top
        while (x - 1 >= 0 && !visited[x - 1][y]) {
            visited[--x][y] = true;
            matrix[x][y] = count;
            count++;
        }
    }
    return matrix;
}