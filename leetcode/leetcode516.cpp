#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    static constexpr int N = 1010;
    int mem[N][N];
public:
    int solve(int x, int y, string &s) {
        if (x < 0 || x >= s.size() || y < 0 || y >= s.size() || x > y) return 0;
        int &v = mem[x][y];
        if (v != -1) return v;
        if (x == y) return v = 1;
        v = max(solve(x + 1, y, s), solve(x, y - 1, s));
        if (s[x] == s[y]) {
            v = 2 + solve(x + 1, y - 1, s);
        }
        // cout << " x: " << x << " y: " << y << " len: " << v << endl;
        return v;
    }

    int longestPalindromeSubseq(string s) {
        memset(mem, -1, sizeof mem);
        return solve(0, s.size() - 1, s);
    }
};

int main() {
    auto so = Solution();
    cout << so.longestPalindromeSubseq("bbbab") << " res: 4" << endl;
    cout << so.longestPalindromeSubseq("cbbd") << " res: 2" << endl;
}