#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 1e3, INF = 1e9;

int n, m, Q;
int d[N][N];

inline void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> Q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }


    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        d[x][y] = min(d[x][y], z);
    }

    floyd();

    while (Q--) {
        int x, y;
        cin >> x >> y;
        if (d[x][y] > INF / 2) cout << "impossible" << endl;
        else cout << d[x][y] << endl;
    }

    return 0;
}