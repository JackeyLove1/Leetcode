#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>

using namespace std;

using ll = long long;
using PII = pair<int, int>;

const int N = 1e6 + 10, M = 1250;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline ll qsm(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline ll qsc(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = a * 2 % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    fhj();
    int n;
    cin >> n;
    while (n--){
        ll a, b, c;
        cin >> a >> b >> c;
        cout << qsm(a, b, c) << endl;
    }
    return 0;
}