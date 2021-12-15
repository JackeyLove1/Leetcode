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
    bool carPooling(vector<vector<int>> &trips, int capacity) {
        sort(trips.begin(), trips.end(), [](const vector<int> &x, const vector<int> &y) {
            return x[0] == y[0] ? x[1] < y[1] : x[0] > y[0];
        });

        vector<int> persons(1000, 0);
        for (auto &trip : trips) {
            int bg = trip[1], ed = trip[2], nums = trip[0];
            for (int i = bg; i < ed; ++i) {
                persons[i] += nums;
                if (persons[i] > capacity) {
                    return false;
                }
            }
        }
        return true;
    }
};