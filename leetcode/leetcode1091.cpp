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
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        const int n = grid.size();
        if (grid[0][0] || grid[n - 1][n - 1]) return -1;
        if(n == 1) return 1;
        constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
        constexpr int dy[] = {1, 0, -1, 0, -1, 1, 1, -1};
        // BFS, end = {n-1, n-1}
        using PII = pair<int, int>;
        queue<PII> q;
        q.push({0, 0});
        grid[0][0] = 1;
        int cnt = 0;
        while (!q.empty()) {
            int sz = q.size();
            ++cnt;
            for (int i = 0; i < sz; ++i) {
                auto t = q.front();
                q.pop();
                for (int j = 0; j < 8; ++j) {
                    int x0 = dx[j] + t.first, y0 = dy[j] + t.second;
                    if (x0 < 0 || y0 < 0 || x0 >= n || y0 >= n) continue;
                    if (grid[x0][y0]) continue;
                    if (x0 == n - 1 && y0 == n - 1) return cnt + 1;
                    // push and add flag
                    q.push({x0, y0});
                    grid[x0][y0] = 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> vec = {{0, 1},
                               {1, 0}};
    cout << s.shortestPathBinaryMatrix(vec) << " res: 2" << endl;
}