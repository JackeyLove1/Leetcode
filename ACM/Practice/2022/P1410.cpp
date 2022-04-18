#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 2200, M = 550;
using ll = long long;
int f[N][N];
constexpr int INF = 0x3f3f3f3f;
int n, m;
int a[N];

int main() {
    fhj();
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) cin >> a[i];
        memset(f, 0x3f, sizeof f);
        f[1][1] = -1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (f[i][j] != INF) {
                    if (a[i] < a[i + 1]) {
                        f[i + 1][j + 1] = min(f[i][j], f[i + 1][j + 1]);
                    }
                    if (f[i][j] < a[i + 1]) {
                        f[i + 1][i - j + 1] = min(f[i + 1][i + 1 - j], a[i]);
                    }
                }
            }
        }
        if (f[n][n / 2] != INF) cout << "Yes!" << endl;
        else cout << "No!" << endl;
    }
    return 0;
}