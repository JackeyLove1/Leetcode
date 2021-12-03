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
constexpr int N = 15;
int w[N][N], f[N * 2][N][N];
int n;

int main() {
    fhj();
    cin >> n;
    int a, b, c;
    while (cin >> a >> b >> c, (a || b || c)) w[a][b] = c;
    for (int k = 2; k <= 2 * n; ++k) {
        for (int i1 = 1; i1 <= n; i1++) {
            for (int i2 = 1; i2 <= n; i2++) {
                int j1 = k - i1, j2 = k - i2;
                if (j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n) {
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
    cout << f[n * 2][n][n];
    return 0;
}