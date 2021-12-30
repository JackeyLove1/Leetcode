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
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>
#include <tuple>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        text1 = static_cast<const string>(text1);
        text2 = static_cast<const string>(text2);
        vector<vector<int>> f(1010, vector<int>(1010, 0));
        // f[0][0] = 1;
        for (int i = 1; i <= text1.size(); ++i) {
            for (int j = 1; j <= text2.size(); ++j) {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
                if (text1[i - 1] == text2[j - 1]) {
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
                }
            }
        }
        return f[text1.size()][text2.size()];
    }
};

int main() {
    Solution s;
    cout << s.longestCommonSubsequence("abcde", "ace") << " res: 3" << endl;
}