#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    using PII = pair<int, int>;
    map<PII, int> cache;
public:
    int solve(string &s, string &t, int m, int n) {
        if (m < -1 || n < -1 || m < n) return 0;
        PII p = {m, n};
        if (cache.count(p)) return cache[p];
        cache[p] = 0;
        int &v = cache[p];
        v = solve(s, t, m - 1, n);
        if (s[m] == t[n]) {
            v += solve(s, t, m - 1, n - 1);
        }
        // cout << "m: " << m << " n: " << n << " res: " << v << endl;
        return v;
    }

    int numDistinct(string s, string t) {
        if (s.size() < t.size()) return 0;
        cache.clear();
        int m = s.size(), n = t.size();
        for (int i = -1; i <= m; i++) cache[{i, -1}] = 1; // edge
        return solve(s, t, m - 1, n - 1);
    }
};

int main() {
    auto s = Solution();
    cout << s.numDistinct("rabbbit", "rabbit") << " res: 3" << endl;
    cout << s.numDistinct("babgbag", "bag") << " res: 5" << endl;
}