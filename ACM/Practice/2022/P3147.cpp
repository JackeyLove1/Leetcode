#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <list>
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

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e5, M = 550;
constexpr int INF = 0x3f3f3f3f;
using ll = long long;

int f[N][N];
// int f[M][M];
int nums[N];
int n;


int main() {
    fhj();
    cin >> n;
    int res = INT_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        res = max(res, nums[i]);
    }
    // init
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; ++i) f[i][i] = nums[i];
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                if (f[i][k] != -1 && f[i][k] == f[k + 1][j]) {
                    f[i][j] = max(f[i][j], f[i][k] + 1);
                    res = max(res, f[i][j]);
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}
