#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// 最长回文子序列
int LBS(string s) {
    int n = s.length();
    vector<vector<int> > dp(n, vector<int>(n, 0));
    // base case
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][n - 1];
}

// test function
int main() {
    string s = "cbxabyc";
    cout << "size is " << s.size() << "  length is " << s.length() << endl;
    cout << "LBS is " << LBS(s) << endl;
    return 0;
}