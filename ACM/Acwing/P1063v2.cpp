#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>
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

constexpr int N = 210;
int q[N];
int n;
int f[N][N];

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> q[i];
        q[i + n] = q[i];
        f[i][i] = q[i];
    }
    for (int len = 2; len <= n + 1; ++len) {
        for (int i = 1; i + len - 1 <= 2 * n; ++i) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; ++k) {
                f[i][j] = max(f[i][j], f[i][k] + f[k][j] + q[i] * q[k] * q[j]);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = max(res, f[i][i + n]);
    }
    cout << res << endl;
    return 0;
}