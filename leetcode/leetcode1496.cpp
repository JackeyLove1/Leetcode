#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    bool isPathCrossing(string path) {
        using PII = pair<int, int>;
        map<PII, bool> m;
        int x = 0, y = 0;
        m[{x, y}] = true;
        for (auto &ch : path) {
            if (ch == 'N') {
                ++x;
            } else if (ch == 'E') {
                --y;
            } else if (ch == 'S') {
                --x;
            } else {
                // ch == 'W'
                ++y;
            }
            if (m.count({x, y})) return true;
            m[{x, y}] = true;
        }
        return false;
    }
};