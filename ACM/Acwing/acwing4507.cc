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

constexpr int N = 3e5 + 100, M = N * 2;
int pre[N], w[N];

int main() {
    fhj();
    memset(pre, 0, sizeof pre);
    memset(w, 0, sizeof w);
    map<PII, int> mp;
    int n;
    cin >> n;
    ll res = 0;
    mp[{0, 0}]++;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        pre[i] = w[i] ^ pre[i - 1];
        res += mp[{pre[i], !(i % 2)}];
        ++mp[{pre[i], i % 2}];
    }
    cout << res << endl;
    return 0;
}