#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

int maxProfit(vector<int> &prices) {
    if (prices.empty()) return 0;
    int n = prices.size();
    int f[n][2];
    f[0][0] = 0, f[0][1] = -prices[0];
    for (int i = 1; i < n; i++) {
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - prices[i]);
        f[i][0] = max(f[i - 1][0], f[i - 1][1] + prices[i]);
    }
    return f[n - 1][0];
}