// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int solve(string &s) {
    int n = s.size();
    vector<vector<int>> f(n + 10, vector<int>(n + 10, -1));
    // 记忆话搜索
    function<int(int, int)> dp = [&](int i, int j) -> int {
        if (f[i][j] != -1) return f[i][j];
        f[i][j] = 0;
        int &v = f[i][j];
        if (i >= j || (j - i) % 2 == 0) return v;
        if (i + 1 == j) {
            v = s[i] != s[j];
            return v;
        }
        v = s[i + 1] == s[i] && s[j] == s[j - 1] && dp(i + 1, j - 1);
        return v;
    };
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp(i, j) == 1) ++cnt;
        }
    }
    return cnt;
}

int main() {
    string s = "001101";
    cout << solve(s) << " res: 4" << endl;
    return 0;
}