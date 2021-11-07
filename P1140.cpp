#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 110;
int dp[N][N];
string sa, sb;
int la, lb;
constexpr int tab[5][5] =
        {
                {5,  -1, -2, -1, -3},
                {-1, 5,  -3, -2, -4},
                {-2, -3, 5,  -2, -2},
                {-1, -2, -2, 5,  -1},
                {-3, -4, -2, -1, 0}
        };
int a[N], b[N];

int main() {
    fhj();
    cin >> la >> sa >> lb >> sb;
    for (int i = 1; i <= la; i++) for (int j = 1; j <= lb; j++) dp[i][j] = -2e8;
    for (int i = 1; i <= la; i++) {
        if (sa[i - 1] == 'A') a[i] = 0;
        if (sa[i - 1] == 'C') a[i] = 1;
        if (sa[i - 1] == 'G') a[i] = 2;
        if (sa[i - 1] == 'T') a[i] = 3;
    }
    for (int i = 1; i <= lb; i++) {
        if (sb[i - 1] == 'A') b[i] = 0;
        if (sb[i - 1] == 'C') b[i] = 1;
        if (sb[i - 1] == 'G') b[i] = 2;
        if (sb[i - 1] == 'T') b[i] = 3;
    }
    for (int i = 1; i <= la; i++) dp[i][0] = dp[i - 1][0] + tab[a[i]][4];
    for (int i = 1; i <= lb; i++) dp[0][i] = dp[0][i - 1] + tab[b[i]][4];
    for (int i = 1; i <= la; i++)
        for (int j = 1; j <= lb; j++) {
            dp[i][j] = max(dp[i][j], dp[i][j - 1] + tab[b[j]][4]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + tab[a[i]][4]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + tab[a[i]][b[j]]);
        }
    printf("%d", dp[la][lb]);
    return 0;
}
