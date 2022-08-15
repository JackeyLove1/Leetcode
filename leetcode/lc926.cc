#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

constexpr int N = 2010, M = 4000010;

class Solution {
public:
    int minFlipsMonoIncr(string s) {
        const int n = s.size();
        int zeros = 0, ones = 0;
        for (const auto &c: s) {
            if (c == '0') ++zeros;
            else ++ones;
        }
        int res = zeros;
        int l = 0, r = zeros;
        for (const auto &c: s) {
            if (c == '1') {
                ++l;
            } else {
                --r;
            }
            res = min(res, l + r);
        }
        return res;
    }
};