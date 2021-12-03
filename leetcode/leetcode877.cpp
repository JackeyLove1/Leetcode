#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
public:
    static constexpr int N = 510;
    int f[N][N][2]; // 1 先手，0后手
    vector<int> nums;

    int solve(int i, int j, int k) {
        if (i > j) return 0;
        int &v = f[i][j][k];
        if (v != -1) return v;
        if (k == 1) {
            v = max(solve(i + 1, j, 0) + nums[i],
                    solve(i, j - 1, 0) + nums[j]);
        } else {
            v = min(solve(i + 1, j, 1),
                    solve(i, j - 1, 1));
        }
        // cout << "k: " << k << " i: " << i << " j: " << j << " res: " << v << endl;
        return v;
    }

    bool stoneGame(vector<int> &piles) {
        // int sum = accumulate(piles.begin(), piles.end(), 0);
        int n = piles.size();
        if (n <= 2) return true;
        nums = move(piles);
        // 初始化
        memset(f, -1, sizeof f);
        for (int i = 0; i < n; i++) {
            f[i][i][1] = nums[i];
            f[i][i][0] = 0;
        }
        int first = solve(0, n - 1, 1);
        int second = solve(0, n - 1, 0);
        // cout << "first: " << first << " second: " << second << endl;
        return first > second;
    }
};

int main() {
    vector<int> nums = {5, 3, 4, 5};
    auto s = Solution();
    cout << s.stoneGame(nums) << " res: true" << endl;
    return 0;
}