#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 2e3 + 100;
// int v[N], w[N], s[N];
int f[N];

struct good {
    int v, w;
};

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<good> goods;
    int v, w, s;
    for (int i = 0; i < n; i++) {
        cin >> v >> w >> s;
        for (int k = 1; k <= s; k <<= 1) {
            goods.push_back({v * k, w * k});
            s -= k;
        }
        if (s) goods.push_back({v * s, w * s});
    }

    for (int i = 0; i < goods.size(); i++) {
        for (int j = m; j >= goods[i].v; j--) {
            f[j] = max(f[j], f[j - goods[i].v] + goods[i].w);
        }
    }

    cout << f[m] << endl;
    return 0;
}