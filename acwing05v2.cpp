#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int N = 2200;
int n, m;
int v, w, s;
int f[N];

struct good {
    int v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<good> goods;
    for (int i = 0; i < n; i++) {
        cin >> v >> w >> s;
        for (int k = 1; k <= s; k <<= 1) {
            goods.push_back({v * k, w * k});
            s -= k;
        }
        if (s) goods.push_back({s * v, s * w});
    }

    for (auto &g: goods) {
        auto&[v0, w0] = g;
        for (int j = m; j >= v0; j--) {
            f[j] = max(f[j], f[j - v0] + w0);
        }
    }

    cout << f[m] << endl;
    return 0;
}