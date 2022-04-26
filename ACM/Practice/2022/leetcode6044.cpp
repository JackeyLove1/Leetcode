#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <list>
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

static inline int cnt_(int x) {
    return __builtin_popcount(x);
}

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 100010, M = 3100010;

int n, m;

class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &persons) {
        vector<int> start, end;
        start.reserve(flowers.size()), end.reserve(flowers.size());
        for (const auto &flower : flowers) {
            start.emplace_back(flower[0]);
            end.push_back(flower[1]);
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());
        vector<int> res;
        res.reserve(persons.size());
        for (const auto &p : persons) {
            int s = upper_bound(start.begin(), start.end(), p) - start.begin();
            int e = lower_bound(end.begin(), end.end(), p) - end.begin();
            if (s > e) res.push_back(s - e);
            else res.push_back(0);
        }
        return res;
    }
};