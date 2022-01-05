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
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        int sz = graph.size();
        vector<vector<int>> prev(sz);
        vector<int> d(sz);
        for (int i = 0; i < sz; ++i) {
            for (const int to : graph[i]) {
                prev[to].push_back(i);
            }
            d[i] = graph[i].size();
        }
        vector<int> res;
        queue<int> q;
        for (int i = 0; i < sz; ++i) {
            if (!d[i]) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            res.push_back(t);
            for (const auto from : prev[t]) {
                if (--d[from] == 0) {
                    q.push(from);
                }
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> g1 = {{1, 2},
                              {2, 3},
                              {5},
                              {0},
                              {5},
                              {},
                              {}};
    auto v1 = s.eventualSafeNodes(g1);
    print(v1);
}