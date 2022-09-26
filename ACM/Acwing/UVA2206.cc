#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100, M = 65, INF = 0x3f3f3f3f;
constexpr auto P = 131;
char s[N];
ull h[N], p[N];
int n, m;

inline ull get_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

static unordered_map<ull, int> mp;
static unordered_map<int, int> pos;

inline void str_hash() {
    memset(h, 0, sizeof h);
    memset(p, 0, sizeof p);
    mp.clear(), pos.clear();
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] * P + s[i];
        p[i] = p[i - 1] * P;
    }
}

inline bool check(int len) {
    auto flag = false;
    for (int l = 1; l + len - 1 <= n; ++l) {
        auto r = l + len - 1;
        auto hs = get_hash(l, r);
        if (++mp[hs] >= m) {
            flag = true;
            pos[len] = l;
        }
    }
    return flag;
}

int main() {
    while (scanf("%d", &m) == 1 && m) {
        scanf("%s", s + 1);
        n = strlen(s + 1) + 1;
        str_hash();
        if (!check(1)) {
            printf("none\n");
            continue;
        }
        int l = 1, r = n;
        while (l < r) {
            auto mid = l + r + 1 >> 1;
            if (check(mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        printf("%d %d\n", l, pos[l]-1);
    }
    return 0;
}