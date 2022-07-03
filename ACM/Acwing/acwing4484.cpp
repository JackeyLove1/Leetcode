#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <cmath>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    fhj();
    int T;
    cin >> T;
    ll p, q, b;
    while (T--) {
        cin >> p >> q >> b;
        ll d = gcd(p, q);
        q /= d;
        while (q > 1) {
            int d = gcd(q, b);
            if (d == 1) break;
            while (q % d == 0) q /= d;
        }
        if (q > 1) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}