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

constexpr int N = 2e3 + 10, M = 2e5 + 100;
int f[N][N];
char a[N], b[N];
int n, m;


int main() {
    fhj();
    scanf("%s", a + 1);
    n = strlen(a + 1);
    scanf("%s", b + 1);
    m = strlen(b + 1);
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) f[i][0] = i;
    for (int i = 1; i <= m; ++i) f[0][i] = i;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
            if (a[i] == b[j]) {
                f[i][j] = min(f[i][j], f[i - 1][j - 1]);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}