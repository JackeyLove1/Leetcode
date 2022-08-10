#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e6 + 1000;
// int n, k;

class Solution {
public:
    int longestIdealString(string s, int k) {
        int f[27];
        memset(f, 0, sizeof f);
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto c = s[i] - 'a';
            for (int j = max(0, c - k); j <= min(26, c + k); ++j) {
                f[c] = max(f[c], f[j]);
            }
            f[c] += 1;
            res = max(res, f[c]);
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.longestIdealString("eduktdb", 15) << " expect: 5" << endl;
    cout << s.longestIdealString("acfgbd", 2) << " expect: 4" << endl;
    return 0;
}