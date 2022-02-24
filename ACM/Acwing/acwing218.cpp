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

const int N = 14;
const double INF = 1e20;

int A, B, C, D;
double f[N][N][N][N][5][5];

double dp(int a, int b, int c, int d, int x, int y) {
    double &v = f[a][b][c][d][x][y];
    if (v >= 0) return v;
    int as = a + (x == 0) + (y == 0);
    int bs = b + (x == 1) + (y == 1);
    int cs = c + (x == 2) + (y == 2);
    int ds = d + (x == 3) + (y == 3);

    if (as >= A && bs >= B && cs >= C && ds >= D) return v = 0;
    int sum = a + b + c + d + (x != 4) + (y != 4);
    sum = 54 - sum;
    if (sum <= 0) return v = INF;
    v = 1;
    if (a < 13) v += (13.0 - a) / sum * dp(a + 1, b, c, d, x, y);
    if (b < 13) v += (13.0 - b) / sum * dp(a, b + 1, c, d, x, y);
    if (c < 13) v += (13.0 - c) / sum * dp(a, b, c + 1, d, x, y);
    if (d < 13) v += (13.0 - d) / sum * dp(a, b, c, d + 1, x, y);

    if (x == 4) {
        double t = INF;
        for (int i = 0; i < 4; ++i) t = min(t, 1.0 / sum * dp(a, b, c, d, i, y));
        v += t;
    }
    if (y == 4) {
        double t = INF;
        for (int i = 0; i < 4; ++i) t = min(t, 1.0 / sum * dp(a, b, c, d, x, i));
        v += t;
    }
    return v;
}

int main() {
    fhj();
    cin >> A >> B >> C >> D;

    memset(f, -1, sizeof f);
    double t = dp(0, 0, 0, 0, 4, 4);
    if (t > INF / 2) t = -1;

    printf("%.3lf\n", t);
    return 0;
}