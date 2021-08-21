#include <iostream>
#include <cstring>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

constexpr int N = 220;

int f[N][N], w[N];

int n;

int solve(int i, int j) {
    if (i == j) return 0;
    int &v = f[i][j];
    if (v != -1) return v;
    v = 0;
    for (int k = i + 1; k < j; k++) {
        v = max(v, solve(i, k) + solve(k, j) + w[i] * w[j] * w[k]);
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i + n] = w[i];
    }
    memset(f, -1, sizeof f);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, solve(i, i + n));
    }
    cout << res << endl;
    return 0;
}