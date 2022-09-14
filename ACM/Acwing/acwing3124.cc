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

constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f, M = 26;

inline int popcount(int x) {
    return __builtin_popcount(x);
}

ll bsgs(ll a, ll b, ll p) {
    if(1 % p == b % p) return 0;
    int k = std::sqrt(p) + 1;
    unordered_map<ll, ll> hash;
    for (ll i = 0, j = b % p; i < k; ++i){
        hash[j] = i;
        j = j * a % p;
    }
    ll ak = 1;
    for (ll i = 0; i < k; i ++ ) ak = ak * a % p;

    for (ll i = 1, j = ak; i <= k; i ++ )
    {
        if (hash.count(j)) return i * k - hash[j];
        j = j * ak % p;
    }
    return -1;
}

int main() {
    int a, p, b;
    while (cin >> a >> p >> b, a || p || b){
        auto res = bsgs(a, b, p);
        if (res == -1) cout << "No Solution" << endl;
        else cout << res << endl;
    }
    return 0;
}