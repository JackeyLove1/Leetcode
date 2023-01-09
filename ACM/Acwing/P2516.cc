#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 5e3 + 5, MOD = 1e8;
int f[2][N], g[N][N];

int main() {
    fhj();
    string s1, s2;
    cin >> s1 >> s2;
    s1.pop_back(), s2.pop_back();
    const int n = s1.size(), m = s2.size();
    s1.insert(0, " "), s2.insert(0, " ");
    for (int i = 0; i <= m; i++) g[0][i] = 1; g[1][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cur = i % 2;
            g[cur][j] = 0;
            f[cur][j] = std::max({f[cur ^ 1][j], f[cur][j - 1], f[cur][j]});
            if (s1[i] == s2[j]) {
                f[cur][j] = std::max(f[cur ^ 1][j - 1] + 1, f[cur][j]);
            }
            if (s1[i] == s2[j]) g[cur][j] += g[cur^1][j - 1];
            if (f[cur][j] == f[cur][j - 1]) g[cur][j] += g[cur][j - 1];
            if (f[cur][j] == f[cur ^ 1][j]) g[cur][j] += g[cur ^ 1][j];
            if (f[cur][j] == f[cur ^ 1][j - 1]) g[cur][j] -= g[cur ^ 1][j - 1];
            g[cur][j] %= MOD;
        }
    }
    cout << f[n % 2][m] << endl;
    cout << g[n % 2][m] << endl;
    return 0;
}