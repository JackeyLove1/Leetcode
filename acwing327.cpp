#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include <functional>
#include <queue>

using namespace std;

constexpr int MOD = 1e8, N = 15, M = 1 << 12;

int f[N][M];
vector<int> head[M];
vector<int> state;
int g[N];

int n, m, k;

inline bool check(int state) {
    return !(state & (state << 1));
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> k;
            g[i] |= !k << j;
        }
    }

    for (int i = 0; i < 1 << m; i++) {
        if (check(i)) {
            state.push_back(i);
        }
    }

    for (auto &a :state) {
        for (auto &b : state) {
            if (!(a & b)) {
                head[a].push_back(b);
            }
        }
    }

    f[0][0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (auto &a : state) {
            if (!(a & g[i])) {
                for (auto &b : head[a]) {
                    f[i][a] = (f[i][a] + f[i - 1][b]) % MOD;
                }
            }
        }
    }

    cout << f[n + 1][0] << endl;
    return 0;
}