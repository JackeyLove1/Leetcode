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

constexpr int N = 1e5 + 100, M = 65, INF = 0x3f3f3f3f;

ll f[N];
PII master[M];
vector<PII> slave[M];

int main() {
    fhj();
    int n, m;
    cin >> m >> n;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if (!c) {
            master[++cnt] = {a, a * b};
        } else {
            slave[c].emplace_back(a, a * b);
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        for (int j = m; j > 0; --j) {
            const auto sz = slave[i].size();
            for (int k = 0; k < (1 << sz); ++k) {
                auto v = master[i].first, w = master[i].second;
                for (int l = 0; l < sz; ++l) {
                    if (k & (1 << l)) {
                        v += slave[i][l].first;
                        w += slave[i][l].second;
                    }
                    if (j >= v) {
                        f[j] = std::max(f[j], f[j - v] + w);
                    }
                }
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}