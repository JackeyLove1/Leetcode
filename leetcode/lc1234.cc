#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

class Solution {
public:
    int balancedString(string s) {
        const int n = s.size() / 4;
        int l = 0, r = s.size() - 1;
        unordered_map<char, int> um;
        while (um[s[l]] < n && l < r) ++um[s[l]], ++l;
        // cout << l << endl;
        if (l == r) return 0;
        while (um[s[r]] < n && l < r)++um[s[r]],--r;
        // cout << r << endl;
        return r - l + 1;
    }
};

int main() {
    Solution s;
    cout << s.balancedString("QQER") << " res: 1" << endl;
    cout << s.balancedString("QWER") << " res: 0" << endl;
    cout << s.balancedString("QQQW") << " res: 2" << endl;
    cout << s.balancedString("WWQQRRRRQRQQ") << " res: 4" << endl;
}