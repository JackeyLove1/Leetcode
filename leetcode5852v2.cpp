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
    int minimizeTheDifference(vector<vector<int>> &mat, int target) {
        int n = mat.size(), m = mat[0].size();
        const int N = 4901;
        bitset<N> f[n + 10];
        f[0] = 0;
        for(int i = 0; i < m; i++) f[0][mat[0][i]] = 1;
        for (int i = 1; i < n; i++) {
            f[i] = 0;
            for (int j = 0; j < m; j++) {
                f[i] |= f[i - 1] << mat[i][j];
            }
        }
        int ans = N;
        for (int i = 0; i < N; i++) {
            if (f[n-1][i]) {
                ans = min(ans, abs(target - i));
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