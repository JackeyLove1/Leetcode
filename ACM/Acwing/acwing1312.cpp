#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

int n, l, r;
const int N = 1e5 + 10, mod = 1e6 + 3;
int f[N][100];

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> l >> r;
        memset(f, 0, sizeof f);
        int m = r - l + 1;
        for (int i = 0; i <= m; ++i) f[i][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i][j] = (f[i - 1][j] + f[i][j - 1]) % mod;
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res = (res + f[m][i]) % mod;
        }
        cout << res << endl;
    }
    return 0;
}