#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
int n, a[N];
int ch[N * 31][2], idx;

inline void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int j = (x >> i) & 1;
        if (!ch[p][j]) ch[p][j] = ++idx;
        p = ch[p][j];
    }
}

inline int query(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; --i) {
        int j = (x >> i) & 1;;
        if (ch[p][!j]) {
            res += (1 << i);
            p = ch[p][!j];
        } else {
            p = ch[p][j];
        }
    }
    return res;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], insert(a[i]);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = std::max(res, query(a[i]));
    }
    cout << res << endl;
    return 0;
}