// 凑零钱问题
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int coinChange(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
//    int res = INT_MAX;
    for (auto coin : coins) {
        dp[coin] = 1;
    }
    for (int i = 0; i < dp.size(); i++) {
        for (auto coin : coins) {
            if (i - coin < 0) continue;
            dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    return (dp[amount] == amount + 1) ? -1 : dp[amount];
}

// Test function
int main() {
    vector<int> coins({1, 2, 5});
    int amount = 11;
    cout << "the result is(answer is 3) " << coinChange(coins, amount) << endl;
    return 0;
}