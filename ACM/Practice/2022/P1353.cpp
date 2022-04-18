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

constexpr int N = 1e4 + 100, M = 550;
using ll = long long;
ll f[N][M];
int d[N];
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i > j) f[i][0] = max({f[i][0], f[i - 1][0], f[i - j][j]});
            if (j > 0) f[i][j] = max(f[i - 1][j - 1] + d[i], f[i][j]);
        }
    }
    cout << f[n][0] << endl;
    return 0;
}
