#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    int findMinDifference(const vector<string> &timePoints) {
        using PII = pair<int, int>;
        vector<PII> times;
        times.reserve(timePoints.size() + 5);
        for (const auto &str : timePoints) {
            times.emplace_back(stoi(str.substr(0, 2)), stoi(str.substr(3, 2)));
        }
        sort(times.begin(), times.end(), [](const PII &p1, const PII &p2) {
            return p1.first == p2.first ? p1.second > p2.second : p1.first > p2.first;
        });
        const int total = 24 * 60;
        auto timeDiff = [&](const PII &p1, const PII &p2) -> int {
            int h_diff = p1.first - p2.first;
            int m_diff = p1.second - p2.second;
            int cur = abs(h_diff * 60 + m_diff);
            return min(cur, total - cur);
        };

        int res = INT_MAX;
        for (int i = 0; i < times.size() - 1; ++i) {
            res = min(res, timeDiff(times[i], times[i + 1]));
        }
        res = min(res, timeDiff(times.front(), times.back()));
        return res;
    }
};