#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int MOD = 100003, N = 1e5 + 100;
int n, k;
int f[N];

int main() {
    cin >> n >> k;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int start = max(0, i - k);
        for (int j = start; j < i; ++j) {
            f[i] = (f[i] + f[j]) % MOD;
        }
        // cout << "i: " << i << " start: " << start << " f[i]: " << f[i] << endl;
    }
    cout << f[n] << endl;
    return 0;
}