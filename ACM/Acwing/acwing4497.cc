#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 1005;
int n, m;

int main() {
    fhj();
    cin >> n;
    ll a, b, c;
    while (n--) {
        cin >> a >> b >> c;
        cout << (a + b + c) / 2 << endl;
    }
    return 0;
}