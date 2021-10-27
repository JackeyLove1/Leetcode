// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
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
#include <numeric>


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

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 55, M = 2e5 + 100;

class Solution {
public:
    using PII = pair<int, int>;
    map<PII, bool> m;
    int ex, ey;

    bool solve(int x, int y) {
        PII p = {x, y};
        if (m.count(p)) return m[p];
        bool &b = m[p] = false;
        if (x > ex || y > ey) return b;
        if (x == ex && y == ey) return b = true;
        return b = solve(x + y, y) || solve(x, x + y);
    }

    bool reachingPoints(int sx, int sy, int tx, int ty) {
        ex = tx, ey = ty;
        return solve(sx, sy);
    }
};