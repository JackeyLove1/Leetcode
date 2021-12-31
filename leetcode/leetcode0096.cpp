#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        s1 = static_cast<const string>(s1);
        s2 = static_cast<const string>(s2);
        s3 = static_cast<const string>(s3);
        int p1 = 0, p2 = 0;
        for (const auto ch : s3) {
            if (p1 < s1.size() && ch == s1[p1]) {
                ++p1;
                continue;
            }
            if (p2 < s2.size() && ch == s2[p2]) {
                ++p2;
                continue;
            }
            return false;
        }
        return true;
    }
};

class Solution2 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        auto f = vector<vector<int> >(s1.size() + 1, vector<int>(s2.size() + 1, false));

        int n = s1.size(), m = s2.size(), t = s3.size();

        if (n + m != t) {
            return false;
        }

        f[0][0] = true;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                int p = i + j - 1;
                if (i > 0) {
                    f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
                }
                if (j > 0) {
                    f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
                }
            }
        }

        return f[n][m];
    }
};

int main() {
    Solution s;
    cout << s.isInterleave("aabcc", "dbbca", "aadbbcbcac") << " res: 1" << endl;
    // cout << s.isInterleave("aabcc", "dbbca", "aadbbbaccc") << " res: 0" << endl;
    // cout << s.isInterleave("", "", "") << " res: 1" << endl;
    return 0;
}