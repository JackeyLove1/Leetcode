#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100, M = 1e4 + 100, INF = 0x3f3f3f3f;
int n, m;
char s[N], p[N];
int ne[N];

inline void solve() {
    scanf("%s", p + 1);
    n = std::strlen(p + 1);
    memset(ne, 0, sizeof ne);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    int ans = n;
    for (int i = ne[n]; i; i = ne[i]) {
        int k = n - i;
        if (n % k == 0) ans = 0;
        ans = std::min(ans, k - n % k);
    }
    cout << ans << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}