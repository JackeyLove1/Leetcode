#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>

using namespace std;

using ll = long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 110, M = 1250, INF = 0x3f3f3f3f;

int f[N];
constexpr int w[]{150, 200, 350};

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> m;
        memset(f, 0, sizeof f);
        for (int i = 0; i < 3; ++i) {
            for (int j = w[i]; j <= m; ++j) {
                f[j] = std::max(f[j], f[j-w[i]] + w[i]);
            }
        }
        cout << m - f[m] << endl;
    }
}