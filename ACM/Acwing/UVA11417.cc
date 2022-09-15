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

inline int popcount(int x) {
    return __builtin_popcount(x);
}

int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b, a % b);
}

constexpr int N = 5000007;

ll solve(int n){
    ll res = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = i + 1; j <= n; ++j){
            res += gcd(i, j);
        }
    }
    return res;
}

int n;
int main(){
    fhj();
    while (cin >> n && n){
        cout << solve(n) << endl;
    }
    return 0;
}