#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

template<typename T>
inline void print1(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

class Solution {
public:
    using PII = pair<int, int>;

    int maxDistance(vector<vector<int>> &grid) {
        int n = grid.size();
        // vector<vector<bool>> st(n, vector<bool>(n, false));
        vector<vector<int>> dist(n, vector<int>(n, -1));
        // priority_queue<PII, vector<PII>, greater<>> heap;
        queue<PII> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        if (q.empty() || q.size() == n * n) return -1;
        // BFS
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        int res = 0;
        while (!q.empty()) {
            auto[x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int x0 = x + dx[i], y0 = y + dy[i];
                if (x0 >= n || x0 < 0 || y0 >= n || y0 < 0) continue;
                if (dist[x0][y0] >= 0) continue;
                dist[x0][y0] = dist[x][y] + 1;
                // cout << "x0: " << x0 << " y0: " << y0 << " dist: " << dist[x0][y0] << endl;
                res = max(dist[x0][y0], res);
                q.push({x0, y0});
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> nums = {{1, 0, 1},
                                {0, 0, 0},
                                {1, 0, 1}};
    auto s = Solution();
    cout << s.maxDistance(nums) << endl;
}