#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

int n, m;
constexpr int N = 1e3 + 10;
int v[N], w[N];
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
        for (int j = m; j >= v[i]; j--) {
            f[j] = max(f[j - v[i]] + w[i], f[j]);
        }
    }
    cout << f[m] << endl;
    return 0;
}