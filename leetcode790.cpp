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

constexpr int N = 1e3 + 100, M = 1e4 + 10, INF = 0x3f3f3f3f;

class Solution {
public:
    unordered_map<int, int> f;
    constexpr static int MOD = 1e9 + 7;

    int solve(int n) {
        if (f.count(n)) return f[n];
        int &v = f[n] = 0;
        if (n == 0) return v = 1;
        if (n == 1) return v = 1;
        if (n == 2) return v = 2;
        if (n == 3) return v = 5;
        v = 2 * solve(n - 1) % MOD;
        v = (v + solve(n - 3)) % MOD;
        return v;
    }

    int numTilings(int n) {
        return solve(n);
    }
};