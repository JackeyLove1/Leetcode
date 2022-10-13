#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <numeric>
#include <cmath>

using namespace std;
using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

class Solution {
public:
    int numberOfPaths(vector<vector<int>> &grid, int k) {
        constexpr int mod = 1e9 + 7;
        const int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> f(m, vector<vector<int>>(n, vector<int>(51, 0)));
        f[0][0][grid[0][0] % k] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int left = grid[i][j] % k;
                for (int q = 0; q < k; ++q) {
                    if (i > 0) {
                        f[i][j][(left + q) % k] = (f[i][j][(left + q) % k] + f[i - 1][j][q]) % mod;
                    }
                    if (j > 0) {
                        f[i][j][(left + q) % k] = (f[i][j][(left + q) % k] + f[i][j - 1][q]) % mod;
                    }
                }

            }
        }
        return f[m - 1][n - 1][0];
    }
};