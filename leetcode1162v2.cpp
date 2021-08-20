#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int maxDistance(vector<vector<int>> &grid) {
        using PII = pair<int, int>;
        queue<PII> q;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m + 1, vector<int>(n + 1, -1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    q.emplace(i, j);
                    dist[i][j] = 0;
                }
            }
        }
        if (q.size() == m * n || q.empty()) return -1;
        int res = 0;
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        while (q.size()) {
            auto[x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int x0 = x + dx[i], y0 = y + dy[i];
                if (x0 >= m || x0 < 0 || y0 >= n || y0 < 0) continue;
                if (dist[x0][y0] != -1) continue;
                dist[x0][y0] = dist[x][y] + 1;
                res = max(res, dist[x0][y0]);
                q.push({x0, y0});
            }
        }
        return res;
    }
};

int main() {

}