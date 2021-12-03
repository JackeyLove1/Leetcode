#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    const int debug = 0;

    int minimizeTheDifference(vector<vector<int>> &mat, int target) {
        int n = mat.size(), m = mat[0].size();
        const int N = 4901;
        vector<vector<bool>> f(n + 10, vector<bool>(N, false));
        f[0][0] = true;
        // for (int i = 0; i < n; i++) f[0][mat[0][i]] = true;
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k < m; k++) {
                for (int j = mat[i - 1][k]; j < N; j++) {
                    if (f[i - 1][j - mat[i - 1][k]]) {
                        f[i][j] = true;
                        // if (debug) cout << "i: " << i << " j:" << j << " f[i][j]:" << f[i][j] << endl;
                    }
                }
            }
        }
        int ans = 4900;
        for (int i = 0; i < N; i++) {
            if (f[n][i]) {
                ans = min(ans, abs(target - i));
                // if (debug) cout << "num: " << i << " ans: " << ans << endl;
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> mat = {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9}};
    auto s = Solution();
    cout << s.minimizeTheDifference(mat, 13) << " res:0" << endl;
    return 0;
}