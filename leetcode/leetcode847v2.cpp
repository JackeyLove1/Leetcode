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
    int shortestPathLength(vector<vector<int>> &graph) {
        int n = graph.size();
        // cur, state, dist
        using TIII = tuple<int, int, int>;
        queue<TIII> q;
        vector<vector<bool>> visited(n, vector<bool>(1 << n, false));
        // init
        for (int i = 0; i < n; i++) {
            q.emplace(i, 1 << i, 0);
            visited[i][1 << i] = true;
        }
        int res = 0x3f3f3f3f;
        while (q.size()) {
            auto[cur, state, dist] = q.front();
            q.pop();
            if (state == (1 << n) - 1) {
                return dist;
            }
            for (auto &v : graph[cur]) {
                int state0 = state | (1 << v);
                if (!visited[v][state0]) {
                    visited[v][state0] = true;
                    q.emplace(v, state0, dist + 1);
                }
            }
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    vector<vector<int>> nums = {{1, 2, 3},
                                {0},
                                {0},
                                {0}};
    cout << s.shortestPathLength(nums) << " res: 4" << endl;
    return 0;
}