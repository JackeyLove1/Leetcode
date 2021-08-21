#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include <functional>
#include <queue>

using namespace std;

int n, m, k;
constexpr int MOD = 1e8, N = 15, M = 1 << 12;

vector<int> state;
vector<int> head[M];
int w[N];
int f[N][M];

inline bool check(int state) {
    return !(state & (state >> 1));
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    memset(f, 0, sizeof f);
    memset(w, 0, sizeof w);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> k;
            w[i] |= !k << j;
        }
    }

    for (int i = 0; i < 1 << m; i++) {
        if (check(i)) state.push_back(i);
    }

    for (auto &a : state) {
        for (auto &b : state) {
            if (!(a & b)) head[a].push_back(b);
        }
    }

    f[0][0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (auto &a : state) {
            if (!(w[i] & a)) {
                for (auto &b : head[a]) {
                    f[i][a] = (f[i][a] + f[i - 1][b]) % MOD;
                }
            }
        }
    }

    cout << f[n + 1][0] << endl;
    return 0;
}