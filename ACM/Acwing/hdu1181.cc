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
#include <cmath>

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

constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f, M = 26;
char s[N];
int d[M][M];

void inline floyed() {
    for (int k = 0; k < 26; ++k) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = std::min(d[i][k] + d[k][j], d[i][j]);
                }
            }
        }
    }
}

int n, m;

int main() {
    memset(d, 0x3f, sizeof d);
    while (scanf("%s", s) != EOF) {
        if (s[0] == '0') {
            floyed();
            auto res = d['b' - 'a']['m' - 'a'];
            if (res != INF) cout << res << endl;
            else cout << -1 << endl;
            memset(d, 0x3f, sizeof d);
        } else {
            d[s[0] - 'a'][s[strlen(s) - 1] - 'a'] = 1;
        }
    }
}