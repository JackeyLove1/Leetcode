#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>

using namespace std;
using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100, MOD = 5000011;
int n, k;
ll s[N], f[N];

int main() {
    fhj();
    cin >> n >> k;
    s[0] = f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i] = s[std::max(i - k - 1, 0)];
        s[i] = (f[i] + s[i - 1]) % MOD;
    }
    cout << s[n] << endl;
    return 0;
}