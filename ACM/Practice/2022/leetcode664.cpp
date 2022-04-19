#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 2200, M = 550;
constexpr int INF = 0x3f3f3f3f;
using ll = long long;


class Solution {
public:
    int strangePrinter(const string &s) {
        int sz = s.size();
        vector<vector<int>> f(sz + 5, vector<int>(sz + 5, 100000));
        for (int i = 0; i < sz; ++i) {
            f[i][i] = 1;
        }
        for (int len = 2; len <= sz; ++len) {
            for (int i = 0; i + len - 1 < sz; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) f[i][j] = min(f[i][j], f[i][j - 1]);
                for (int k = i; k < j; ++k) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
                }
                // cout <<"i: " << i <<" j: " << j << " res: " << f[i][j] << endl;
            }
        }
        return f[0][sz - 1];
    }
};

int main() {
    auto s = Solution();
    cout << s.strangePrinter("aba") << endl;
    return 0;
}