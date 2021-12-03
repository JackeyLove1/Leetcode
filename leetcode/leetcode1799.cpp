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
constexpr int N = 1000;

class Solution {
public:
    inline int _gcd(int a, int b) {
        return b == 0 ? a : _gcd(b, a % b);
    }

    inline int cnt(int x) {
        return __builtin_popcount(x);
    }

    int maxScore(vector<int> &nums) {
        int n = nums.size();
        vector<vector<int>> gcd(n + 2, vector<int>(n + 2, 0));
        vector<int> f(1 << n, 0);
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                f[(1 << i) | (1 << j)] = _gcd(nums[i], nums[j]);
            }
        }
        for (int state = 0; state < (1 << n); ++state) {
            if (cnt(state) % 2) continue;
            for (int u = state; u; u = (u - 1) & state) {
                if (cnt(state) - cnt(u) == 2) {
                    f[state] = max(f[state], f[u] + (cnt(state) / 2) * f[state - u]);
                }
            }
        }
        cout << f[(1 << n) - 1] << endl;
    }
};