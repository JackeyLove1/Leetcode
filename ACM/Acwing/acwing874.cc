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

using namespace std;
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

constexpr int N = 1e6 + 10;
int primes[N], cnt;
bool st[N];
int eluer[N];

inline void get_euler(int n) {
    cnt = 0;
    memset(st, false, sizeof st);
    eluer[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            primes[cnt++] = i;
            eluer[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; ++j) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                eluer[t] = eluer[i] * primes[j];
                break;
            }
            eluer[t] = eluer[i] * (primes[j] - 1);
        }
    }
}

int main() {
    fhj();
    int n;
    cin >> n;
    get_euler(n);
    ll res = 0;
    for (int i = 1; i <= n; ++i) res += eluer[i];
    cout << res << endl;
    return 0;
}