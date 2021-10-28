#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 110, M = 1e5;
int n, m;
int f[M];

struct good {
    int v, w;

    good(int _v, int _w) : v(_v), w(_w) {}
};

int main() {
    fhj();
    vector<good> goods;
    cin >> n >> m;
    int v, w, s;
    for (int i = 1; i <= n; ++i) {
        cin >> v >> w >> s;
        for (int k = 1; k <= s; k <<= 1) {
            goods.emplace_back(k * v, k * w);
            s -= k;
        }
        if (s) {
            goods.emplace_back(s * v, s * w);
        }
    }
    for (auto &g : goods) {
        for (int j = m; j >= g.w; j--) {
            f[j] = max(f[j], f[j - g.w] + g.v);
        }
    }
    cout << f[m] << endl;
    return 0;
}