#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    using ll = long long;
    static constexpr ll INF = INT_MAX;
    unordered_map<int, ll> cache;
public:
    ll solve(vector<int> &coins, int amount) {
        if (amount < 0) return INT_MAX;
        if (cache.count(amount)) return cache[amount];
        cache[amount] = INF;
        ll &v = cache[amount];
        for (int i = 0; i < coins.size(); i++) {
            v = min(v, solve(coins, amount - coins[i]) + 1);
        }
        return v;
    }

    int coinChange(vector<int> &coins, int amount) {
        if (amount == 0) return 0;
        if (coins.empty()) return -1;
        int n = coins.size();
        cache.clear();
        cache[0] = 0;
        for (auto &coin : coins) cache[coin] = 1;
        ll res = solve(coins, amount);
        if (res >= INT_MAX) res = -1;
        return res;
    }
};

int main() {
    vector<int> nums = {1, 2, 5};
    int amount = 11;
    auto s = Solution();
    cout << s.coinChange(nums, amount) << " res:3" << endl;
    vector<int> nums1 = {2};
    int amount1 = 3;
    cout << s.coinChange(nums1, amount1) << " res: -1" << endl;
    return 0;
}