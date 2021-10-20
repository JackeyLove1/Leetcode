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

constexpr int N = 1e6 + 100, INF = 0x7fffffff;

int a[N], f[N], pre[N];

int main() {
    fhj();
    int m, n;
    int maxn;
    while (cin >> m >> n && m && n) {
        memset(f, 0, sizeof f);
        memset(pre, 0, sizeof pre);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= m; ++i) {
            maxn = -INF;
            for (int j = i; j <= n; ++j) {
                f[j] = max(f[j - 1] + a[j], pre[j - 1] + a[j]);
                pre[j - 1] = maxn;
                maxn = max(maxn, f[j]);
            }
        }
        cout << maxn << endl;
    }
    return 0;
}
