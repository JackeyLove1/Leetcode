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

// DFS解法，超时
class SolutionDFS {
private:
    static constexpr int MOD = 1e9 + 7;
    int n_ = 0, minProfit_ = 0;
    int count = 0;
public:
    void solve(vector<int> &group, vector<int> &profit, int curIndex, int curPeople, int curProfit) {
        if (curPeople > n_) return;
        if (curIndex == group.size()) {
            if (curProfit >= minProfit_) {
                count++;
            }
            return;
        }
        solve(group, profit, curIndex + 1, curPeople + group[curIndex], curProfit + profit[curIndex]);
        solve(group, profit, curIndex + 1, curPeople, curProfit);
    }

    int profitableSchemes(int n, int minProfit, vector<int> &group, vector<int> &profit) {
        n_ = n, minProfit_ = minProfit;
        count = 0;
        solve(group, profit, 0, 0, 0);
        return count;
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