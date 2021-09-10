#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>

using namespace std;

constexpr int N = 1e2 + 10, MAXN = 1e6 + 10;
int n;
int a[N], b[N];
bitset<MAXN> f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        f[i].reset();
        for (int j = a[i]; j <= b[i]; ++j) {
            f[i] |= f[i-1] << (j * j);
        }
    }
    cout << f[n].count() << endl;
    return 0;
}