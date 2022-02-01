#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 1e3 + 100;

class Solution {
public:
    int maxSumRangeQuery(vector<int> &nums, const vector<vector<int>> &requests) {
        const int mod = 1e9 + 7;
        unordered_map<int, int> um;
        for (const auto &req : requests) {
            for (int i = req[0]; i <= req[1]; ++i) {
                // cout << "num: " << i << endl;
                um[i]++;
            }
        }
        sort(nums.begin(), nums.end(), [](int p1, int p2) {
            return p1 > p2;
        });
        priority_queue<int, vector<int>, less<>> heap;
        for (const auto&[k, v] : um) {
            heap.push(v);
        }
        int res = 0;
        for (int i = 0, t = heap.size(); i < t; ++i) {
            // cout << "heap: " << heap.top() <<" nums[i]: " << nums[i] << endl;
            res = (heap.top() * nums[i] + res) % mod;
            heap.pop();
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> v1 = {{1, 3},
                              {0, 1}};
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << s.maxSumRangeQuery(nums, v1) << " res: 19" << endl;
}