#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

using ll = long long;
constexpr int N = 3002;

int n, m, a, b;
int x[N], y[N], mp[256];
int d[4][4];
char s[N];

ll dp[N][N][3];

int main() {
    mp['A'] = 0;
    mp['T'] = 1;
    mp['G'] = 2;
    mp['C'] = 3;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        x[i] = mp[s[i]];
    scanf("%s", s + 1);
    m = strlen(s + 1);
    for (int i = 1; i <= m; ++i)
        y[i] = mp[s[i]];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            scanf("%d", &d[i][j]);
    scanf("%d%d", &a, &b);
    for (int i = max(n, m); i; --i) {
        dp[0][i][0] = dp[i][0][0] = dp[0][i][2] = dp[i][0][1] = -(1LL << 60);
        dp[0][i][1] = dp[i][0][2] = -a - b * (i - 1);
    }
    dp[0][0][1] = dp[0][0][2] = -(1LL << 60);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            dp[i][j][0] = *max_element(dp[i - 1][j - 1], dp[i - 1][j - 1] + 3) + d[x[i]][y[j]];
            dp[i][j][1] = max(max(dp[i][j - 1][0] - a, dp[i][j - 1][1] - b), dp[i][j - 1][2] - a);
            dp[i][j][2] = max(max(dp[i - 1][j][0] - a, dp[i - 1][j][2] - b), dp[i - 1][j][1] - a);
        }
    printf("%lld\n", *max_element(dp[n][m], dp[n][m] + 3));
    return 0;
}