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
    vector<int> avoidFlood(vector<int> &rains) {
        unordered_map<int, int> used;
        deque<int> pins;
        vector<int> res(rains.size(), 0);
        for (int i = 0; i < rains.size(); ++i) {
            if (rains[i] && !used.count(rains[i])) {
                res[i] = -1;
                used.insert({rains[i], i});
                continue;
            }
            if (!rains[i]) {
                pins.push_back(i);
                continue;
            }
            if (used.count(rains[i])) {
                if (pins.empty()) return {};
                int v = used[rains[i]];
                if (pins.back() < v) {
                    return {};
                }
                int t = -1;
                auto iter = lower_bound(pins.begin(), pins.end(), v);
                t = *iter;
                pins.erase(iter);
                res[t] = rains[i];
                res[i] = -1;
                used[rains[i]] = i;
            }
        }
        while (!pins.empty()) {
            int t = pins.back();
            pins.pop_back();
            res[t] = 1;
        }
        return res;
    }
};

int main() {
    Solution s;

    vector<int> rains = {1, 2, 3, 4};
    auto res1 = s.avoidFlood(rains);
    print(res1);
    cout << "res1: {-1,-1,-1,-1}" << endl;

    vector<int> r2 = {1, 2, 0, 0, 2, 1};
    auto res2 = s.avoidFlood(r2);
    print(res2);
    cout << "res2: {-1,-1,2,1,-1,-1}" << endl;

    vector<int> r3 = {0, 1, 1};
    auto res3 = s.avoidFlood(r3);
    print(res3);
    cout << "res3: empty !" << endl;

    vector<int> r4 = {1, 0, 2, 0, 2, 1};
    auto res4 = s.avoidFlood(r4);
    print(res4);
    cout << "res4: {-1,1,-1,2,-1,-1}" << endl;

    vector<int> r5 = {1, 0, 2, 3, 0, 1, 2};
    auto res5 = s.avoidFlood(r5);
    print(res5);
    cout << "res5: [-1,1,-1,-1,2,-1,-1]" << endl;
}