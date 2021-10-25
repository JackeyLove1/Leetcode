// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 81, M = 1e3 + 100, INF = 0x3f3f3f3f;

#define in(x) x=read()
#define MAXN 81
#define k m-(R-L)
#define bll __int128

using namespace std;

inline int read() {
    int X = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + ch - '0', ch = getchar();
    return X * w;
}

int n, m;
int num[MAXN];
bll ans, p[MAXN], f[MAXN][MAXN];

void print(bll x) {
    if (!x) return;
    if (x) print(x / 10);
    putchar(x % 10 + '0');
}

bll dp(int L, int R)//记忆化搜索
{
    if (f[L][R] != -1) return f[L][R];
    if (R - L >= 1) f[L][R] = max(num[L] * p[k] + dp(L + 1, R), dp(L, R - 1) + num[R] * p[k]);
    else f[L][R] = num[L] * p[k];
    return f[L][R];
}

int main() {
    fhj();
    in(n);
    in(m);
    p[0] = 1;
    for (int i = 1; i <= m; i++) p[i] = p[i - 1] * 2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) in(num[j]);
        memset(f, -1, sizeof(f));
        ans += dp(1, m);
    }
    if (!ans) printf("0");
    else print(ans);
    return 0;
}