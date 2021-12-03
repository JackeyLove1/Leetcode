#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

int maxProfit(vector<int> &prices) {
    int n = prices.size();
    // vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
    if (prices.empty()) return 0;
    int res = 0, minV = 1e9;
    for (int i = 0; i < n; i++) {
        minV = min(minV, prices[i]);
        res = max(res, prices[i] - minV);
    }
    return res;
}