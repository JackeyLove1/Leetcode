#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <unordered_map>

using namespace std;

class Solution {
private:
    // 记忆化搜索
    static constexpr int MOD = 1e9 + 7;
    static constexpr int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
    int _m, _n;
public:
    int solve(int moves, int x, int y, vector<vector<vector<int>>> &cache) {
        if (x >= _m || y >= _n || x < 0 || y < 0) return 1;
        if (moves == 0) return 0;
        int &v = cache[moves][x][y];
        if (v != -1) return v;
        v = 0;
        for (int i = 0; i < 4; i++) {
            int x0 = x + dx[i], y0 = y + dy[i];
            v += solve(moves - 1, x0, y0, cache);
            v %= MOD;
        }
        return v;
    }

    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        auto cache = vector<vector<vector<int>>>(maxMove + 1, vector<vector<int>>(m + 1, vector<int>(n, -1)));
        _m = m, _n = n;
        return solve(maxMove, startRow, startColumn, cache);
    }
};