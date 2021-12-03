#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 110;
int n, k1;

struct Node {
    int h, w;

    bool operator<(const Node &rhs) const {
        return h < rhs.h;
    }
} g[N];

int f[N][N];

int main() {
    fhj();
    cin >> n >> k1;
    for (int i = 1; i <= n; ++i) {
        cin >> g[i].h >> g[i].w;
    }
    sort(g + 1, g + n + 1);
    int m = n - k1;
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) {
        f[i][1] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k < i; k++) {
                f[i][j] = min(f[i][j], f[k][j - 1] + abs(g[i].w - g[k].w));
            }
        }
    }
    int res = 1e6;
    for (int i = 1; i <= n; ++i) {
        res = min(res, f[i][m]);
    }
    cout << res << endl;
    return 0;
}

