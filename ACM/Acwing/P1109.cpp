#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int f[55];

const int maxn = 1e5;
int n, m, l, r, a[maxn], sum, in, out;

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    cin >> l >> r;
    for (int i = 1; i <= n; i++) {
        if (a[i] > r)out += a[i] - r;
        if (a[i] < l)in += l - a[i];
    }
    if (sum > n * r || sum < n * l)cout << -1 << endl;
    else cout << max(out, in) << endl;
    return 0;
}