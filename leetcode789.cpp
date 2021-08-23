#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

class Solution {
public:
    bool escapeGhosts(vector<vector<int>> &ghosts, vector<int> &target) {
        using cv = const vector<int>;
        auto f = [](cv &v1, cv &v2) {
            return abs(v1[0] - v2[0]) + abs(v1[1] - v2[1]);
        };
        vector<int> src = {0, 0};
        int dist = f(src, target);
        for (auto &ghost : ghosts) {
            if (f(ghost, target) <= dist)
                return false;
        }
        return true;
    }
};