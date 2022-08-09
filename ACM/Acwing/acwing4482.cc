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

int main() {
    fhj();
    int n;
    cin >> n;
    map<int, int> mp;
    int res = 0, x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        ++mp[x];
        res = max(res, mp[x]);
    }
    cout << res << endl;
    return 0;
}