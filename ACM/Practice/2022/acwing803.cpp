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
int n, m;
using PII = pair<int, int>;
vector<PII> nums;
#define x first
#define y second

int main() {
    fhj();
    cin >> n;
    nums.reserve(n + 10);
    int l, r;
    for (int i = 0; i < n; ++i) {
        cin >> l >> r;
        nums.emplace_back(l, r);
    }
    sort(nums.begin(), nums.end());
    int cnt = 0;
    l = 0, r = 0;
    for (const auto &num : nums) {
        // cout << num.x <<" " << num.y << endl;
        if (cnt == 0) {
            ++cnt;
            l = num.x, r = num.y;
        } else if (num.x > r) {
            ++cnt;
            l = num.x, r = num.y;
        } else {
            r = max(num.y, r);
        }
        // cout << "l: " << l <<" r: " << r << endl;
    }
    cout << cnt << endl;
    return 0;
}