class Solution {
public:
    int minScoreTriangulation(vector<int> &A) {
        const int n = A.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                for (int m = i + 1; m < j; m++) {
                    if (dp[i][j] == 0)
                        dp[i][j] = A[i] * A[j] * A[m] + dp[i][m] + dp[m][j];
                    else
                        dp[i][j] = min(dp[i][j], A[i] * A[j] * A[m] + dp[i][m] + dp[m][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
