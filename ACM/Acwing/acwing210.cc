#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>
#include <cmath>

using namespace std;
using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;
int n, m;
ll a[N];

int main() {
    fhj();
    int T;
    cin >> T;
    for (int C = 1; C <= T; C++) {
        cout << "Case #" << C <<":"<< endl;
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        int k = 0;
        for (int i = 62; i >= 0; --i) {
            for (int j = k; j < n; ++j) {
                if ((a[j] >> i) & 1) {
                    swap(a[k], a[j]);
                    break;
                }
            }
            if (!((a[k] >> i) & 1)) continue;
            for (int j = 0; j < n; ++j) {
                if (j != k && ((a[j] >> i) & 1)) {
                    a[j] ^= a[k];
                }
            }
            ++k;
            if (k == n) break;
        }
        reverse(a, a + k);
        cin >> m;
        while (m--) {
            ll x;
            cin >> x;
            if (k < n) x--;
            if (x >= (1l << k)) cout << -1 << endl;
            else {
                ll res = 0;
                for (int i = 0; i < k; ++i) {
                    if (x & (1l << i)) res ^= a[i];
                }
                cout << res << endl;
            }
        }
    }
    return 0;
}