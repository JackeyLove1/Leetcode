#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100, M = 1e4+100, INF = 0x3f3f3f3f;
int n, m;
int s[N], p[M];
int ne[M];

inline void solve() {
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) cin >> p[i];
    memset(ne, 0, sizeof ne);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    auto flag = false;
    for (int i = 1, j = 0; i <= m; i++) {   // 在模式串p中找到与匹配串s中第i位匹配的第一位j
        // next数组存放的是字符串的前缀和后缀能匹配的字符个数的最大值
        while (j && s[i] != p[j + 1]) j = ne[j]; // 下一位不匹配，取下一位匹配项
        if (s[i] == p[j + 1]) j++; // 匹配成功j移动到下一位
        if (j == n) {
            cout << i - n + 1<< endl;
            flag = true;
            break;
        }
    }
    if (!flag) cout << -1 << endl;
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}