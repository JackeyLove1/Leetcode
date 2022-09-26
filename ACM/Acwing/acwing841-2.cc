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

inline ull get(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] * P + s[i];
        p[i] = p[i - 1] * P;
    }
    while (m--) {
        int l0, r0, l1, r1;
        scanf("%d%d%d%d", &l0, &r0, &l1, &r1);
        if (get(l0, r0) == get(l1, r1)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}