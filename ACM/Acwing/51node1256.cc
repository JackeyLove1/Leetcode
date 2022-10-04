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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using LL = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

constexpr int N = 1e5 + 100;


LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}


int main() {
    int n, m;
    cin >> m >> n;
    LL x, y;
    exgcd(m, n, x, y);
    while (x < 0){
        x += n;
    }
    cout << x << endl;
    return 0;
}