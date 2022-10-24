#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;

inline ll read() {
    ll ans = 0, sgn = 1;
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

constexpr int N = 1e5 + 100;
int n, m, len;
std::array<ll, N> sum, add, w;

inline int get(int idx) {
    return idx / len;
}

void update(int l, int r, int d) {
    if (get(l) == get(r)) {
        for (int i = l; i <= r; ++i) {
            w[i] += d, sum[get(i)] += d;
        }
        return;
    }
    int i = l, j = r;
    while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, ++i;
    while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, --j;
    for (int k = get(i); k <= get(j); ++k) {
        sum[k] += 1l * d * len;
        add[k] += d;
    }
}

ll query(int l, int r) {
    ll res{0};
    if (get(l) == get(r)) {
        for (int i = l; i <= r; ++i) {
            res += w[i] + add[get(i)];
        }
        return res;
    }
    int i = l, j = r;
    while (get(i) == get(l)) res += w[i] + add[get(i)], ++i;
    while (get(j) == get(r)) res += w[j] + add[get(j)], --j;
    for (int k = get(i); k <= get(j); ++k) {
        res += sum[k];
    }
    return res;
}

int main() {
    n = read(), m = read();
    len = std::sqrt(n);
    for (int i = 1; i <= n; ++i) {
        w[i] = read();
        sum[get(i)] += w[i];
    }
    int l, r, d;
    char op[2];
    while (m--) {
        scanf("%s", op);
        l = read(), r = read();
        if (*op == 'C') {
            d = read();
            update(l, r, d);
        } else {
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}