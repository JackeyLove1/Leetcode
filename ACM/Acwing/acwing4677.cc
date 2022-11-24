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
int ne[M];

inline void solve() {
    // cin >> p + 1 >> s + 1;
    scanf("%s%s", p + 1, s + 1);
    n = std::strlen(p + 1), m = std::strlen(s + 1);
    memset(ne, 0, sizeof ne);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    int res = 0;
    for (int i = 1, j = 0; i <= m; i++) {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j++; // 匹配成功j移动到下一位
        if (j == n) {
            ++res;
            j = ne[j];
        }
    }
    cout << res << endl;
}

int main() {
    // fhj();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}