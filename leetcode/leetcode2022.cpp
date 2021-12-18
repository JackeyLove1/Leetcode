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
    vector<vector<int>> construct2DArray(vector<int> &original, int m, int n) {
        if (original.size() != m * n)
            return {};
        vector<vector<int>> res(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res[i][j] = original[i * n + j];
                // cout <<"i: " << i <<" j: " << j << endl;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> num = {1, 1, 1, 1};
    auto res = s.construct2DArray(num, 4, 1);
    for_each(res.begin(), res.end(), [](vector<int> &v) { print(v); });
}