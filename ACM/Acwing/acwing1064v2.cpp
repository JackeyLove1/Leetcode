#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include <functional>
#include <queue>

using namespace std;

constexpr int MOD = 1e8, N = 12, M = 1 << 10, K = 110;

using ll = long long;
ll f[N][K][M];
vector<int> head[M];
int cnt[M];
vector<int> state;
int n, m;

inline bool check(int state) {
    return !(state & (state >> 1));
}

inline int count(int state) {
    int res = 0;
    for (int i = 0; i < n; i++) res += 1 & (state >> i);
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < 1 << n; i++) {
        if (check(i)) {
            state.push_back(i);
            cnt[i] = count(i);
        }
    }

    for (auto &a : state) {
        for (auto &b: state) {
            if (!(a & b) && check(a | b)) {
                head[a].push_back(b);
            }
        }
    }

    f[0][0][0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= m; j++) {
            for (auto &a : state) {
                int c = cnt[a];
                if (j >= c) {
                    for (auto &b : head[a]) {
                        f[i][j][a] += f[i - 1][j - c][b];
                    }
                }
            }
        }
    }

    cout << f[n + 1][m][0];
    return 0;
}