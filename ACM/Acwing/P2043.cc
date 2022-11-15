#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e7 + 100, M = 1e4 + 1;
int primes[N], cnt{0};
bool vis[N];

inline void init() {
    const int n = 1e5 + 1;
    memset(vis, false, sizeof vis);
    for (int i = 2; i <= M; ++i) {
        if (!vis[i]) {
            primes[cnt++] = i;
        }
        for (int j = 0; j < cnt && primes[j] * i <= n; ++j) {
            vis[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    int n;
    cin >> n;
    init();
    for (int i = 0; i < cnt && primes[i] <= n; ++i) {
        int s = primes[i], p = 0;
        int u = n;
        while (u) p += u / s, u /= s;
        cout << s << " " << p << endl;
    }
    return 0;
}