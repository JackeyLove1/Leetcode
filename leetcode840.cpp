// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 500010;

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>> &grid) {
        int res = 0;
        vector<int> st(10, 0);
        std::function<bool(int, int, int)> f = [&](int x, int y, int cur) -> int {
            if (grid[x + 1][y + 1] != 5) return false;
            st.clear();
            for (int i = x; i < x + 3; ++i) {
                for (int j = y; j < y + 3; ++j) {
                    if (grid[i][j] > 9 || grid[i][j] == 0) return false;
                    if (++st[grid[i][j]] > 1) return false;
                }
            }
            // row, col
            for (int i = 0; i < 3; ++i) {
                if (grid[x + i][y + 0] + grid[x + i][y + 1] + grid[x + i][y + 2] != cur) return false;
                if (grid[x + 0][y + i] + grid[x + 1][y + i] + grid[x + 2][y + i] != cur) return false;
            }
            // diag
            if (grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] != cur) return false;
            if (grid[x + 2][y] + grid[x + 1][y + 1] + grid[x][y + 2] != cur) return false;
            return true;
        };

        for (int i = 0; i + 3 <= grid.size(); ++i) {
            for (int j = 0; j + 3 <= grid[0].size(); ++j) {
                int cur = 15;
                if (f(i, j, cur)) ++res;
            }
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    vector<vector<int>> v = {{3, 2, 9, 2, 7},
                             {6, 1, 8, 4, 2},
                             {7, 5, 3, 2, 7},
                             {2, 9, 4, 9, 6},
                             {4, 3, 8, 2, 5}};
    cout << s.numMagicSquaresInside(v) << endl;
}