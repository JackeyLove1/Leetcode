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
constexpr int N = 2e5 + 1000, INF = 1e9, C = 32, M = 19999997;
int a[N], f[N];

int main() {
    fhj();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int res = 1;
    priority_queue<PII, vector<PII>, less<>> pq;
    f[0] = 1;
    for (int i = 1; i < n; ++i) {
        f[i] = 1;
        if (a[i] <= 2 * a[i - 1]) {
            f[i] = max(f[i], f[i - 1] + 1);
            res = max(res, f[i]);
        }
    }
    cout << res << endl;
    return 0;
}