#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
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

constexpr int N = 3100;
int f[N][N];
int a[N], b[N];
int n;

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) {
        int maxv = 1;
        for (int j = 1; j <= n; ++j) {
            f[i][j] = f[i-1][j];
            if(a[i] == b[j]) f[i][j] = max(maxv, f[i][j]);
            if(a[i] > b[j]) maxv = max(maxv, f[i-1][j]+1);
        }
    }
    int res = 0;
    for(int i = 1; i <= n; ++i) res = max(res, f[n][i]);
    cout << res << endl;
    return 0;
}