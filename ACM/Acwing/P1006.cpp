#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
// #include <map>
#include <bitset>
#include <queue>
#include <deque>

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
constexpr int N = 52;
int w[N][N], f[N * 2][N][N];
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    int a, b, c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> w[i][j];
        }
    }
    for (int k = 1; k <= (m + n); ++k) {
        for (int i1 = 1; i1 <= n; i1++) {
            for (int i2 = 1; i2 <= n; i2++) {
                int j1 = k - i1, j2 = k - i2;
                if (j1 >= 1 && j1 <= m && j2 >= 1 && j2 <= m) {
                    int &v = f[k][i1][i2];
                    int t = w[i1][j1];
                    if (i1 != i2) t += w[i2][j2];
                    v = max(v, f[k - 1][i1 - 1][i2 - 1] + t);
                    v = max(v, f[k - 1][i1 - 1][i2] + t);
                    v = max(v, f[k - 1][i1][i2 - 1] + t);
                    v = max(v, f[k - 1][i1][i2] + t);
                }
            }
        }
    }
    cout << f[(m + n)][n][n];
    return 0;
}