#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int maxProfit(vector<int> &prices) {
    int best = 0;
    if(prices.empty()) return 0;
    int lowPrices = prices[0];
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > lowPrices) {
            best = max(best, prices[i] - lowPrices);
        } else {
            best += lowPrices - prices[i];
            lowPrices = prices[i];
        }
    }
    return best;
}