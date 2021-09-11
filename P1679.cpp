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

constexpr int N = 1e6 + 100;
int f[N], s[N];
int n;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) f[i] = i;
    int m = ceil(sqrt(sqrt(n)) + 1);
    for (int i = 1; i <= m; ++i) {
        f[i * i * i * i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; int(pow(j, 4)) <= i; ++j) {
            f[i] = min(f[i], f[i - int(pow(j, 4))] + 1);
        }
    }
    cout << f[n] << endl;
    return 0;
}