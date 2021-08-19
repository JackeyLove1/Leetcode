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
    // 使用记忆化搜索的方法
    using PII = pair<int, int>;
    static constexpr int N = 110;
    const int INF = 1e9;
    map<PII, int> cache;
    bool judge[N][N];

    int solve(string &s, int i, int j) {
        if (i == j) return 1;
        PII p = {i, j};
        if (cache.count(p)) return cache[p];
        cache[p] = INF;
        int &v = cache[p];
        if (judge[i][j]) return v = 1;
        if (s[i] == s[j] && j > i) {
            // 考虑一次打印出来的情况
            v = min(v, solve(s, i, j - 1));
        }
        for (int k = i; k < j; k++) {
            // 两次打印出来的情况
            v = min(v, solve(s, i, k) + solve(s, k + 1, j));
        }
        // cout << "i: " << i << " j: " << j << " v: " << v << endl;
        // cout << "judge[i][j]: " << judge[i][j] << endl;
        return v;
    }

    int strangePrinter(string s) {
        int n = s.size();
        memset(judge, 0, sizeof judge);
        cache.clear();
        for (int i = 0; i < n; i++) { judge[i][i] = true; }
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < j; i++) {
                judge[i][j] = judge[i][j - 1] && (s[j] == s[j - 1]);
                // printf("judge[%d][%d] = %d\n", i, j, judge[i][j]);
            }
        }
        return solve(s, 0, n - 1);
    }
};

int main() {
    auto s = Solution();
    cout << s.strangePrinter("aaabbb") << " res: 2" << endl;
    cout << s.strangePrinter("aba") << " res: 2" << endl;
    return 0;
}