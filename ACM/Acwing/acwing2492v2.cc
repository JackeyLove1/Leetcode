#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

int n, m, len;
constexpr int N = 50100, M = 200010, S = 1000010, INF = 1e9;
int w[N], ans[M];
int cnt[S];

inline int get(int x) {
    return x / len;
}

struct Query {
    int id, l, r;

    bool operator<(const Query &rhs) const {
        return get(l) == get(rhs.l) ? r < rhs.r : get(l) < get(rhs.l);
    }
} q[M];

inline void add(int x, int &res) {
    if (!cnt[x]) ++res;
    ++cnt[x];
}

inline void del(int x, int &res) {
    if (cnt[x] == 1) --res;
    --cnt[x];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    scanf("%d", &m);
    len = max(1, (int) std::sqrt((double) n * n / m));
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = Query{i, l, r};
    }
    sort(q, q + m);
    int res = 0;
    for (int k = 0, i = 0, j = 1; k < m; ++k) {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(w[++i], res);
        while (i > r) del(w[i--], res);
        while (j < l) del(w[j++], res);
        while (j > l) add(w[--j], res);
        ans[id] = res;
    }
    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}