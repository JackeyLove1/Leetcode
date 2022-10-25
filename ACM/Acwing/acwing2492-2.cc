#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

template<typename T>
inline T read() {
    T ans = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            sgn *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * sgn;
}

using ll = long long;
constexpr int N = 1e6 + 100;
int n, m, len;

inline int get(int idx) {
    return idx / len;
}


class Query {
public:
    int idx{}, l{}, r{};

    Query() = default;

    explicit Query(int idx_, int l_, int r_) : idx(idx_), l(l_), r(r_) {}

    bool operator<(const Query &rhs) const {
        auto a = get(l), b = get(rhs.l);
        if (a != b) return a < b;
        return r < rhs.r;
    }

    friend ostream &operator<<(ostream &os, const Query &q) {
        return os << "idx: " << q.idx << " l: " << q.l << " r: " << q.r;
    }
};

std::array<int, N> w{};
std::array<int, N> ans{}, cnt{};
std::array<Query, N> querys{};

inline void add(int idx, int &res) {
    if (!cnt[idx]) ++res;
    ++cnt[idx];
}

inline void del(int idx, int &res) {
    if (cnt[idx] == 1) --res;
    --cnt[idx];
}

int main() {
    n = read<int>();
    len = std::max(1, int(std::sqrt(double(n) * n / m)));
    for (int i = 1; i <= n; ++i) {
        w[i] = read<int>();
    }
    m = read<int>();
    for (int i = 0; i < m; ++i) {
        int l, r;
        l = read<int>(), r = read<int>();
        querys[i] = Query{i, l, r};
    }
    sort(querys.begin(), querys.begin() + m);
    int res = 0;
    for (int k = 0, l = 1, r = 0; k < m; ++k) {
        // auto [idx, ql, qr] = querys[k];
        auto &q = querys[k];
        int idx = q.idx, ql = q.l, qr = q.r;
        while (r < qr) add(w[++r], res);
        while (r > qr) del(w[r--], res);
        while (l < ql) del(w[l++], res);
        while (l > ql) add(w[--l], res);
        ans[idx] = res;
    }
    for (int i = 0; i < m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}