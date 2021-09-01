#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int M = 4e5, N = 500;

int iq[N], eq[N];
int f[M * 2 + N];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    memset(f, -0x3f, sizeof f);
    f[M] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> iq[i] >> eq[i];
        if (iq[i] >= 0) {
            for (int j = 2 * M; j >= iq[i]; j--) {
                f[j] = max(f[j], f[j - iq[i]] + eq[i]);
            }
        } else {
            for (int j = 0; j <= 2 * M + iq[i]; j++) {
                f[j] = max(f[j], f[j - iq[i]] + eq[i]);
            }
        }
    }
    int res = 0;
    for (int i = M; i <= M * 2; i++) {
        if (f[i] > 0) {
            res = max(res, f[i] + i - M);
        }
    }
    cout << res << endl;
    return 0;
}