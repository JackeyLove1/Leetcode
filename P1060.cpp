#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

int n, m;

constexpr int N = 3e5;
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int v, p;
    for (int i = 1; i <= m; i++) {
        cin >> v >> p;
        int w = v * p;
        for (int j = n; j >= v; j--) {
            f[j] = max(f[j], f[j - v] + w);
        }
    }
    cout << f[n] << endl;
    return 0;
}