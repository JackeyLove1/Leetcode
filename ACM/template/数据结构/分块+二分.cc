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
constexpr int N = 1e6 + 100, M = 1e3 + 100;
int n, m, len, cnt{0};
std::array<int, N> add{0}, w{0}, belong{0};
std::vector<int> blocks[M];

inline int find(int bid, int x) {
    auto &block = blocks[bid];
    x = x - add[bid];
    return std::distance(lower_bound(block.begin(), block.end(), x), block.end());
}

inline int get(int idx) {
    return belong[idx];
}

inline void update(int bid) {
    auto &block = blocks[bid];
    block.clear();
    for (int i = (bid - 1) * len + 1; i <= bid * len; ++i) {
        block.push_back(w[i]);
    }
    sort(block.begin(), block.end());
}

inline void change(int l, int r, int d) {
    if (get(l) == get(r)) {
        for (int i = l; i <= r; i++) w[i] += d;
        update(get(l));
    } else {
        int i = l, j = r;
        while (get(i) == get(l)) w[i] += d, i++;
        while (get(j) == get(r)) w[j] += d, j--;
        for (int k = get(i); k <= get(j); k++) add[k] += d;
        update(get(l)), update(get(r));
    }
}

inline int query(int l, int r, int x) {
    int res{0};
    if (get(l) == get(r)) {
        x -= add[get(l)];
        for (int i = l; i <= r; ++i) {
            if (w[i] >= x) ++res;
        }
        return res;
    } else {
        int i = l, j = r;
        while (get(i) == get(l)) {
            if (w[i] >= x - add[get(i)]) ++res;
            i++;
        }
        while (get(j) == get(r)) {
            if (w[j] >= x - add[get(j)]) ++res;
            j--;
        }
        for (int k = get(i); k <= get(j); k++) res += find(k, x);
    }
    return res;
}

int main() {
    n = read<int>(), m = read<int>();
    len = std::sqrt(n);
    for (int i = 1; i <= n; ++i) {
        w[i] = read<int>();
        if (i % len == 1) {
            ++cnt;
            blocks[cnt].reserve(len);
        }
        belong[i] = cnt;
        blocks[cnt].push_back(w[i]);
    }
    for (int i = 1; i <= cnt; ++i) {
        sort(blocks[i].begin(), blocks[i].end());
    }
    int l, r, d;
    char op[2];
    while (m--) {
        scanf("%s", op);
        l = read<int>(), r = read<int>(), d = read<int>();
        if (*op == 'M') {
            change(l, r, d);
        } else {
            printf("%d\n", query(l, r, d));
        }
    }
    return 0;
}