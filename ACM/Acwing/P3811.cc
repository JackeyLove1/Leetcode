#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 3e6 + 100;
using ll = long long;
ll inv[N];

int main() {
    fhj();
    int n, p;
    scanf("%d %d", &n, &p);
    inv[1] = 1;
    cout << inv[1] << endl;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (ll) (p - p / i) * inv[p % i] % p;
        printf("%lld\n", inv[i]);
    }
    return 0;
}