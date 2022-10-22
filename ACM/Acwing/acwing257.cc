#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;
int p[N], rk[N];
int n, m;

int find(int x) {
    return x == p[x] ? x : (p[x] = find(p[x]));
}

inline bool query(int x, int y) {
    return find(x) == find(y);
}

inline void merge(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) {
        if (rk[px] > rk[py]) {
            p[py] = px;
            rk[px] += rk[py];
            rk[py] = 0;
        } else {
            p[px] = py;
            rk[py] += rk[px];
            rk[px] = 0;
        }
    }
}

inline void init(int n) {
    for (int i = 1; i <= n; ++i) {
        p[i] = i, rk[i] = 1;
    }
}

struct man {
    int a, b, c;

    explicit man(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {};

    bool operator<(const man &rhs) const {
        return c < rhs.c;
    }
};

int main() {
    fhj();
    cin >> n >> m;
    vector<man> mans;
    mans.reserve(m);
    init(n * 2);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        mans.emplace_back(a, b, c);
    }
    sort(mans.begin(), mans.end(), [](const auto &m1, const auto &m2) {
        return m1.c > m2.c;
    });
    auto flag = false;
    for (const auto &s: mans) {
        if (query(s.a, s.b)) {
            cout << s.c << endl;
            flag = true;
            break;
        }
        merge(s.a, s.b + n);
        merge(s.b, s.a + n);
    }
    if (!flag) cout << 0 << endl;
    return 0;
}