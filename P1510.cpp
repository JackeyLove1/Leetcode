#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1e4 + 100;
int n, m, v, w, a, b;
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> v >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        for (int j = m; j >= b; j--) {
            f[j] = max(f[j], f[j - b] + a);
        }
    }
    for (int i = 1; i <= m; i++) {
        if (f[i] >= v) {
            cout << m - i << endl;
            return 0;
        }
    }
    cout << "Impossible" << endl;
    return 0;
}