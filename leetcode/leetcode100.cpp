#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int minimumTotal(vector<vector<int>> &triangle) {
        if (triangle.size() == 1) return triangle[0][0];
        for (int i = 1; i < triangle.size(); ++i) {
            for (int j = 0; j < triangle[i].size(); ++j) {
                if (j == triangle[i].size() - 1) {
                    triangle[i][j] += triangle[i - 1][j - 1];
                    continue;
                }
                if (j == 0) {
                    triangle[i][j] += triangle[i-1][j];
                    continue;
                }
                triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
            }
        }
        return *min_element(triangle.back().begin(), triangle.back().end());
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums = {{2},
                                {3, 4},
                                {6, 5, 7},
                                {4, 1, 8, 3}};
    cout << s.minimumTotal(nums);
}