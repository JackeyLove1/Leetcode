#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
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

constexpr int N = 1e6 + 100;

int n, m, len;
int w[N], ans[N];
int cnt[N];

inline int get(int place) {
    return place / len;
}

class Query {
public:
    int id, l, r;

    Query() = default;

    explicit Query(int id_, int l_, int r_) : id(id_), l(l_), r(r_) {}

    bool operator<(const Query &rhs) const {
        int k1 = get(l), k2 = get(rhs.l);
        return k1 == k2 ? r < rhs.r : k1 < k2;
    }
};

inline void add(int idx, int &res) {
    if (!cnt[idx]) ++res;
    ++cnt[idx];
}

inline void del(int idx, int &res) {
    if (--cnt[idx] == 0) --res;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    cin >> m;
    len = max(1, (int)sqrt((double)n * n / m));
    int l, r;
    vector<Query> qs;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        qs.emplace_back(i, l, r);
    }
    sort(qs.begin(), qs.end());
    int res = 0;
    for (int k = 0, i = 0, j = 1; k < m; ++k) {
        l = qs[k].l, r = qs[k].r;
        while (i < r) add(w[++i], res);
        while (i > r) del(w[i--], res);
        while (j < l) del(w[j++], res);
        while (j > l) add(w[--j], res);
        ans[qs[k].id] = res;
    }
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}