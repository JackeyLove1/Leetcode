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

constexpr int N = 1e6, M = 1e3 + 100, INF = 0x3f3f3f3f;

class Solution {
public:
    bool validSquare(vector<int> &p1, vector<int> &p2, vector<int> &p3, vector<int> &p4) {
        using PII = pair<int, int>;
        vector<vector<int>> v;
        v.emplace_back(p1);
        v.emplace_back(p2);
        v.emplace_back(p3);
        v.emplace_back(p4);
        sort(v.begin(), v.end(), [](vector<int> &v1, vector<int> &v2) {
            return v1[0] == v2[0] ? v1[1] < v2[1] : v1[0] < v2[0];
        });
        auto cal = [](vector<int> &v1, vector<int> &v2) -> int {
            return int(pow(v1[0] - v2[0], 2) + pow(v1[1] - v2[1], 2));
        };
        int l1 = cal(v[0], v[1]);
        int l2 = cal(v[0], v[3]);
        int l3 = cal(v[1], v[4]);
        int l4 = cal(v[3], v[4]);
        return l1 == l2 == l3 == l4;
    }
};