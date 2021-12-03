#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

// 动态规划方法
int change(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (auto coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }
    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    cout << change(5, coins) << endl;
    vector<int> coins2 = {3, 5, 7, 8, 9, 10, 11};
    cout << change(500, coins2) << endl;
}