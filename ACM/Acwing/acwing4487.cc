#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
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
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e6 + 1000;

ll a[N], s[N];
int n;

inline bool check(int len) {
    int minn = 0;
    for (int i = 0, j = len; j <= n; ++i, ++j) {
        if (s[i] < s[minn]) minn = i;
        // cout << "len: " << len << " minn:" << minn << " j: " << j << endl;
        // cout << " minn: " << s[minn] << " j: " << s[j] << " target: " << s[j] - s[minn] << endl;
        if (s[j] - s[minn] > 0) return true;
    }
    return false;
}

int main() {
    fhj();
    cin >> n;
    memset(s, 0, sizeof s);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i] - 100;
    }
    int l = 0, r = n, res = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            res = max(res, mid), l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res << endl;
    return 0;
}