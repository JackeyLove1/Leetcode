#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
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
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e5 + 1000;
int a[N], b[N];

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, int> mp;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        ++mp[t];
    }
    for (int i = 0; i < n; ++i) {
        if (mp.count(a[i])) {
            cout << a[i] << " ";
        }
    }
    cout << endl;
    return 0;
}