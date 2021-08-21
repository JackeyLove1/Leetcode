#include <iostream>
#include <cstring>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        s = " " + s, p = " " + p;
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 10, vector<bool>(n + 10, false));
        f[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j] == '*') {
                    f[i][j] = f[i][j - 1] || (i - 1 >= 0 && f[i - 1][j]);
                } else {
                    f[i][j] = i - 1 >= 0 && f[i - 1][j - 1] && (s[i] == p[j] || p[j] == '?');
                }
            }
        }
        return f[m][n];
    }
};

int main() {
    auto s = Solution();
    cout << s.isMatch("aa", "a") << " res:false" << endl;
    cout << s.isMatch("aa", "a*") << " res:true" << endl;
    cout << s.isMatch("aa", "*") << " res:true" << endl;
    return 0;
}