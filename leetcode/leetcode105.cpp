#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int res = 0;
        const int dx[] = {0, 0, 1, 0, -1};
        const int dy[] = {0, 1, 0, -1, 0};
        const int m = grid.size(), n = grid[0].size();
        // 使用DFS
        std::function<void(int, int, int &)> dfs = [&](int x, int y, int &cnt) {
            for (int i = 0; i < 5; ++i) {
                int x0 = x + dx[i], y0 = y + dy[i];
                if (x0 < 0 || x0 >= m || y0 < 0 || y0 >= n) {
                    continue;
                }
                if (grid[x0][y0] == 0) continue;
                grid[x0][y0] = 0;
                ++cnt;
                dfs(x0, y0, cnt);
            }
        };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    int cnt = 0;
                    dfs(i, j, cnt);
                    res = max(res, cnt);
                }
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> grid =
            {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
             {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
             {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
    Solution s;
    cout << s.maxAreaOfIsland(grid) << endl;
}