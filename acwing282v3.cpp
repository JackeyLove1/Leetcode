#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

constexpr int N = 310, INF = 0x3f3f3f3f;

int s[N], f[N][N];
int n;

int solve(int i, int j) {
    if (i == j) return 0;
    int &v = f[i][j];
    if (v != -1) return v;
    v = INF;
    for (int k = i; k < j; k++) {
        v = min(v, solve(i, k) + solve(k + 1, j) + s[j] - s[i - 1]);
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
    memset(f, -1, sizeof f);
    int res = solve(1, n);
    cout << res << endl;
    return 0;
}