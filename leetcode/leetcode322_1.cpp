#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

int coinChange(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (auto coin : coins) {
        for (int i = coin; i <= amount; i++) {
            if(dp[i-coin] != INT_MAX)
                dp[i] = min(dp[i - coin] + 1, dp[i]);
        }
    }
    return (dp[amount] == INT_MAX ) ? -1 : dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    cout << coinChange(coins, 11) << endl;
    vector<int> coins2 = {2};
    cout << coinChange(coins2, 3) << endl;
}