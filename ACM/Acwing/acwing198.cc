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
using ull = __int128;
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

constexpr int primes[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int n, number = 0, maxd = 0;

void dfs(int u, int last, int p, int s) {
    if (s > maxd || (s == maxd && p < number)) {
        maxd = s;
        number = p;
    }
    if (u == 9) return;
    for (int i = 1; i <= last; ++i) {
        if ((ll) p * primes[u] > n) break;
        p *= primes[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}

int main() {
    fhj();
    cin >> n;
    dfs(0, 30, 1, 1);
    cout << number << endl;
    return 0;
}