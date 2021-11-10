#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

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

using bll = __int128;
constexpr int N = 1e3 + 100;
int n, m, k;
int w[N], f[N][N];

int main() {
    fhj();
    cin >> n >> k;
    int x1, y1, x2, y2;
    for (int i = 1; i <= n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        ++f[x1 + 1][y1 + 1];
        ++f[x2 + 1][y2 + 1];
        --f[x1 + 1][y2 + 1];
        --f[x2 + 1][y1 + 1];
    }
    int res = 0;
    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j <= 1000; ++j) {
            f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
            if (f[i][j] == k) ++res;
        }
    }
    cout << res << endl;
    return 0;
}