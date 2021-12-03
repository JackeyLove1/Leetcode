#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std;
constexpr int N = 2e5 + 100, M = 18;
int n, m;
int f[N][M], a[N];

inline void init() {
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; j <= M; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}

inline int query(int l, int r) {
    int s = log(r - l + 1) / log(2);
    return max(f[l][s], f[r - (1 << s) + 1][s]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    init();
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
    return 0;
}