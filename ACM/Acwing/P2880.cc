#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
int f[N][31], g[N][31], nums[N];

void ST_build(int n) {
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = std::max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            g[i][j] = std::min(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
            // cout <<"i: " << i <<" j: " << j <<" f: " << f[i][j] <<" g: " << g[i][j] << endl;
        }
    }

}

inline int query(int l, int r) {
    int cnt = std::log2(r - l + 1), len = 1 << cnt;
    auto maxn = std::max(f[l][cnt], f[r - len + 1][cnt]);
    auto minn = std::min(g[l][cnt], g[r - len + 1][cnt]);
    return maxn - minn;
}

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        f[i][0] = g[i][0] = nums[i];
    }
    ST_build(n);
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
    return 0;
}
