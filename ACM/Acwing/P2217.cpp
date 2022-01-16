// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 13;
double f[N][N][N][N][N];
double nums[N][N];
double s[N][N];

int a, b, n;
double avg;
double sum = 0.0;

double solve(int x1, int y1, int x2, int y2, int k) {
    double &v = f[x1][y1][x2][y2][n];
    if (v != -1) return v;
    if (k == 1) {
        v = s[x2][y2] - s[x2 - 1][y1] - s[x1][y2 - 1] + s[x1][y1];
        v = (v - avg) * (v - avg);
    }
    v = INT_MAX;
    for (int i = x1 + 1; i <= x2; ++i) {
        for (int j = 1; j < k; ++j) {
            v = min(v, solve(x1, i - 1, x2, y2, j) + solve(i, y1, x2, y2, k - j));
        }
    }
    for (int i = y1 + 1; i <= y2; ++i) {
        for (int j = 1; j < k; ++j) {
            v = min(v, solve(x1, i - 1, x2, y2, j) + solve(x1, i, x2, y2, k - j));
        }
    }
    return v;
}

int main() {
    fhj();
    cin >> a >> b >> n;
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            cin >> nums[i][j];
            sum += nums[i][j];
        }
    }
    avg = sum / (a * b);
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            s[i][j] = nums[i][j] + s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
        }
    }
    memset(f, -1, sizeof f);
    solve(1, a, 1, b, n);
    printf("%.2lf", sqrt(f[1][a][1][b][n - 1] / n));
    return 0;
}