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

inline int cnt(int x) {
    return __builtin_popcount(x);
}

static constexpr int N = 2e5 + 100, K = 110;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
using ll = long long;
int n;
using PII = pair<int, int>;
vector<PII> nums;
int a[N];
map<int, PII> m;
#define x first
#define y second

int main() {
    fhj();
    int num;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        if (!m.count(num)) {
            m[num] = {i, i};
        } else {
            m[num].y = i;
        }
    }
    for (const auto&[k, v] : m) {
        nums.emplace_back(v.x, v.y);
    }
    sort(nums.begin(), nums.end(), [](const PII &p1, const PII &p2) {
        return p1.x < p2.x;
    });

    int res = 0;
    int l, r;
    for (const auto &p : nums) {
        if (p.x == 0) {
            continue;
        } else if (p.x < r) {
            r = max(r, p.y);
            l = min(l, p.x);
        } else {
            res++;
            l = p.x;
            r = p.y;
        }
    }
    --res;
    int ans = 1;
    for (int i = 1; i <= res; ++i) {
        ans = (2 * ans) % MOD;
    }
    cout << ans << endl;
    return 0;
}