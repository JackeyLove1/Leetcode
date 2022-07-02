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

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

static constexpr int N = 2e5 + 100;
int a[N];

int main() {
    fhj();
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, a + n);
    int res = n;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j < n && a[j] - a[i] <= k) ++j;
        if (a[j - 1] > a[i]) --res;
    }
    cout << res << endl;
    return 0;
}