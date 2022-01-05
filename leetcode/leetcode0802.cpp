#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>> &obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        const int dx[] = {0, 1}, dy[] = {1, 0};
        vector<vector<int>> res;
        queue<vector<int>> q;
        map<vector<int>, int> mp;
        q.push({0, 0});
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            if (mp.count(t)) continue;
            mp[t] = 1;
            res.push_back(t);
            int x = t[0], y = t[1];
            for (int i = 0; i < 2; ++i) {
                int x0 = x + dx[i], y0 = y + dy[i];
                if (x0 >= m || x0 < 0 || y0 >= n || y0 < 0) continue;
                if (obstacleGrid[x0][y0]) continue;
                if (mp.count({x0, y0})) continue;
                if (x0 == m - 1 && y0 == n - 1) {
                    res.push_back({x0, y0});
                    return res;
                }
                q.push({x0, y0});
            }
        }
        return {};
    }
};

class Solution2 {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>> res;
        int rows = obstacleGrid.size();
        int cols = obstacleGrid[0].size();
        // 先排除边缘情况，起点和重点不可达
        if (obstacleGrid[0][0] == 1 || obstacleGrid[rows-1][cols-1] ==1)
        {
            return res;
        }

        // 初始化
        bool d[rows][cols];
        memset(d, 0, sizeof(bool)*rows*cols);
        d[0][0] = 1;
        // 首列
        for (int i = 1; i < rows; ++i)
        {
            d[i][0] = (obstacleGrid[i][0] == 0) && d[i-1][0];
        }
        // 首行
        for (int j = 1; j < cols; ++j)
        {
            d[0][j] = (obstacleGrid[0][j] == 0) && d[0][j-1];
        }

        // 计算
        for (int i = 1; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                // 这里把两种情况都合并在一起了
                // 先判断是否为0
                // 再判断上一次位置是否可达
                d[i][j] = (obstacleGrid[i][j] == 0) && (d[i-1][j] || d[i][j-1]);
            }
        }

        // 结果
        // 如果不可达，直接返回空结果
        if (!d[rows-1][cols-1])
        {
            return res;
        }
        // 可达，倒序计算
        int i = rows-1;
        int j = cols-1;
        while (i > 0 || j > 0)
        {
            // cout << i << "," << j << endl;
            res.push_back({i, j});
            // 判断上一步是上方的情况是否可达
            if (i > 0 && d[i-1][j])
            {
                --i;
            }
            else
            {
                // 因为最后是可达，所以这里必然有一个可达的, 考虑上一步是左边的情况
                --j;
            }
        }
        // 插入起点
        res.push_back({0,0});
        // 倒序
        reverse(res.begin(), res.end());
        return res;
    }
};
