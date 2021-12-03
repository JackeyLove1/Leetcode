#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <queue>
#include <math.h>

using namespace std;

int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    for (int i = 0; i * i <= n; i++) {
        dp[i*i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; i - j * j >= 1; j++) {
            dp[i] = min(dp[i], dp[i - j * j] + 1);
        }
    }
    return dp[n];
}

int main() {
    cout << numSquares(12) << endl;
    cout << numSquares(13) << endl;
    cout << numSquares(1) << endl;
}