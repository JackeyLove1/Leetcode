#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 110, M = 1e5;

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        if(m < n) return 0;
        using ll = long long;
        vector<vector<ll>> f(m + 2, vector<ll>(n + 2, 0));
        for(int i = 0; i <= m; ++i) f[i][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                f[i + 1][j + 1] = f[i][j+1];
                if (s[i] == t[j]) {
                    f[i + 1][j + 1] = f[i][j] + f[i][j + 1];
                }
            }
        }
        return f[m][n];
    }
};

int main() {
    auto s = Solution();
    cout << s.numDistinct("rabbbit", "rabbit") << endl;
    cout << s.numDistinct("babgbag", "bag") << endl;
    return 0;
}