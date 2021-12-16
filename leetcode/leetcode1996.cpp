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
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>> &properties) {
        // 二分搜索的方式
        sort(properties.begin(), properties.end(), [](const vector<int> &x, const vector<int> &y) {
            return x[0] == y[0] ? x[1] > y[1] : x[0] < y[0];
        });
        int res = 0;
        int right = -1;
        for (int i = properties.size() - 1; i > -1; i--) {
            int x = properties[i][0], y = properties[i][1];
            if (right > y)
                res++;
            right = max(right, y);
        }
        return res;
    }
};
