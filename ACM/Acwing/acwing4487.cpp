#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <cmath>

using namespace std;

static constexpr int N = 1e6 + 100;
int n;
using ll = long long;
ll a[N];

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

bool check(int len) {
    int minl = 0;
    for (int i = len, j = 0; i <= n; ++i, ++j) {
        if (a[minl] > a[j]) minl = j;
        if (a[i] - a[minl] > 0) return true;
    }
    return false;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1] - 100;
    }
    int l = 0, r = n, ans = l;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid, l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}