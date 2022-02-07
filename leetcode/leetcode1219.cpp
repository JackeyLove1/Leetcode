#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution1 {
public:
    int getMaximumGold(vector<vector<int>> &grid) {
        // 经典搜索问题
        const int m = grid.size(), n = grid[0].size();
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        vector<vector<bool>> st(m, vector<bool>(n, false));
        int res = 0;
        using PII = pair<int, int>;
        queue<PII> q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    q.push({i, j});
                    int tmp = 0;
                    while (!q.empty()) {
                        auto t = q.front();
                        q.pop();
                        int x = t.first, y = t.second;
                        tmp += grid[x][y];
                        grid[x][y] = 0;
                        for (int k = 0; k < 4; ++k) {
                            int x0 = x + dx[k], y0 = y + dy[k];
                            if (x0 >= 0 && x0 < m && y0 >= 0 && y0 < n && grid[x0][y0]) {
                                q.push({x0, y0});
                            }
                        }
                    }
                    res = max(res, tmp);
                }
            }
        }
        return res;
    }
};

class Solution {
private:
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int ans = 0;

        function<void(int, int, int)> dfs = [&](int x, int y, int gold) {
            gold += grid[x][y];
            ans = max(ans, gold);

            int rec = grid[x][y];
            grid[x][y] = 0;

            for (int d = 0; d < 4; ++d) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > 0) {
                    dfs(nx, ny, gold);
                }
            }

            grid[x][y] = rec;
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 0) {
                    dfs(i, j, 0);
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> v1 = {{0, 6, 0},
                              {5, 8, 7},
                              {0, 9, 0}};
    cout << s.getMaximumGold(v1) << " res: 24" << endl;
}