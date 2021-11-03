#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
// #include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;
constexpr int N = 1e4 + 100;

int e[N], ne[N], h[N], idx;
int cnt[N];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

class Solution {
public:
    int maxSatisfaction(vector<int> &satisfaction) {
        int n = satisfaction.size();
        sort(satisfaction.begin(), satisfaction.end());
        vector<vector<int>> f(n + 10, vector<int>(n + 10, -1));
        std::function<int(int, int)> solve = [&](int x, int y) -> int {
            if (y > x + 1) return -1e9;
            int &v = f[x][y];
            if (v != -1) return v;
            if (y == 1) return v = satisfaction[x];
            v = -1e9;
            for (int i = 0; i < x; ++i) {
                v = max(v, solve(i, y - 1) + satisfaction[x] * y);
            }
            // cout << "nums[x]: " << satisfaction[x] << " y: " << y << " v: " << v << endl;
            return v;
        };
        int res = 0;
        for (int j = 1; j <= n; ++j) {
            res = max(res, solve(n - 1, j));
        }
        return res;

    }
};

class Solution2 {
public:
    int maxSatisfaction(vector<int> &satisfaction) {
        int n = satisfaction.size();
        sort(satisfaction.begin(), satisfaction.end());
        vector<vector<int>> f(n + 10, vector<int>(n + 10, -1));
        std::function<int(int, int)> solve = [&](int x, int y) -> int {
            if (x >= n) return 0;
            int &v = f[x][y];
            if (v != -1) return v;
            v = 0;
            v = max(v, solve(x + 1, y + 1) + satisfaction[x] * y);
            v = max(v, solve(x + 1, y));
            return v;
        };
        return solve(0, 1);

    }
};

int main() {
    vector<int> nums = {-1, -8, 0, 5, -9};
    auto s = Solution();
    cout << s.maxSatisfaction(nums) << " res: 14" << endl;
    vector<int> nums1 = {4, 3, 2};
    cout << s.maxSatisfaction(nums1) << " res: 20" << endl;
}