class Solution {
public:
    // dynamic programing
    int uniquePaths(int m, int n) {
        // 构建动态规划矩阵
        vector<vector<int>> dp(m, vector<int>(n, 0));
        // 边界初始化为1
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }
        // 动态规划
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i >= 1 && j >= 1) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};