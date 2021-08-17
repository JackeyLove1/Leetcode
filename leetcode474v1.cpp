#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    using PII = pair<int, int>;

    inline PII count(string &str) {
        int m = 0, n = 0;
        for (auto &ch : str) {
            if (ch == '0') m++;
            else n++;
        }
        return {m, n};
    }

    int findMaxForm(vector<string> &strs, int m, int n) {
        int sz = strs.size();
        vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
        for (int k = 0; k < sz; k++) {
            auto&&[zero, one] = count(strs[k]);
            for (int i = m; i >= 0; i--) {
                for (int j = n; j >= 0; j--) {
                    if (i >= zero && j >= one) {
                        f[i][j] = max(f[i][j], f[i - zero][j - one] + 1);
                    }
                }
            }
        }
        return f[m][n];
    }
};

int main() {
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    auto s = Solution();
    cout << s.findMaxForm(strs, 5, 3) << " res: 4" << endl;
}