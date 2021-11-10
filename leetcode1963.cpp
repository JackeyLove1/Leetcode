#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

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

inline int cnt(int x) {
    return __builtin_popcount(x);
}

class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        vector<vector<int>> f(n + 10, vector<int>(n + 10, -1));
        function<int(int, int)> solve = [&](int l, int r) -> int {
            int &v = f[l][r];
            if (v != -1) return v;
            if (l == r) return v = 1e6;
            v = 1e6;
            if (s[l] == '[' && s[r] == ']') {
                if (l + 1 == r) return v = 0;
                v = min(v, solve(l + 1, r - 1));
            }
            if (s[l] == ']' && s[r] == '[') {
                if (l + 1 == r) return v = 1;
                v = min(v, solve(l + 1, r - 1) + 1);
            }
            for (int i = l + 1; i < r; ++i) {
                v = min(v, solve(l, i) + solve(i + 1, r));
            }
            return v;
        };
        return solve(0, n - 1);
    }
};

int main() {
    auto s = Solution();
    cout << s.minSwaps("][][") << " res: 1" << endl;
    cout << s.minSwaps("]][[") << " res: 2" << endl;
    cout << s.minSwaps("][[]") << " res: 1" << endl;
    cout << s.minSwaps("]]][[[") << " res: 2" << endl;
}