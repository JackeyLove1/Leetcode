#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    static constexpr int MOD = 1e9 + 7;

    int profitableSchemes(int n, int minProfit, vector<int> &group, vector<int> &profit) {
        int len = group.size();
        vector<vector<vector<int>>> f(len + 2, vector<vector<int>>(n + 2, vector<int>(minProfit + 1, 0)));
        f[0][0][0] = 1;
        for (int i = 1; i <= len; i++) {
            int member = group[i - 1], profits = profit[i - 1];
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= minProfit; k++) {
                    if (j >= member) {
                        f[i][j][k] = (f[i - 1][j][k] + f[i - 1][j - member][max(0, k - profits)]) % MOD;
                    } else {
                        f[i][j][k] = f[i - 1][j][k];
                    }
                }
            }
        }
        int sum = 0;
        for (int j = 0; j <= n; j++) {
            sum = (sum + f[len][j][minProfit]) % MOD;
        }
        return sum;
    }
};

int main() {
    vector<int> group = {2, 2}, profit = {2, 3};
    auto s = Solution();
    cout << s.profitableSchemes(5, 3, group, profit) << " res:2" << endl;
    vector<int> group1 = {2, 3, 5}, profit1 = {6, 7, 8};
    cout << s.profitableSchemes(10, 5, group1, profit1) << " res:7" << endl;
    return 0;
}