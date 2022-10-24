#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e8 + 100;
vector<int> primes;
int n, m;
bool st[N];

inline void init() {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes.push_back(i);
        for (int j = 0; j < primes.size() && primes[j] * i <= n; ++j) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    fhj();
    cin >> n >> m;
    primes.reserve(1e6 + 100);
    init();
    while (m--) {
        int x;
        cin >> x;
        cout << primes[x-1] << endl;
    }
    return 0;
}