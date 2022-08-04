#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 110, MOD = 998244353;
int n;
ll f[N][N];
int q[N], s[N];

int main() {
    fhj();
    cin >> n;
    auto pre = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> q[i];
        s[i] = s[i - 1] + q[i];
        pre = min(s[i], pre);
    }
    auto sum = accumulate(q + 1, q + n + 1, 0);
    cout << sum - pre << endl;
    return 0;
}