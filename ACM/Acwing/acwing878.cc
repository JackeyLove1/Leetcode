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

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    auto d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}


int main() {
    fhj();
    int n, m;
    cin >> n;
    while (n--) {
        int a, b, x, y;
        cin >> a >> b >> m;
        auto d = exgcd(a, m, x, y);
        if (b % d != 0) cout << "impossible" << endl;
        else cout << 1l * b / d * x % m << endl;
    }
    return 0;
}