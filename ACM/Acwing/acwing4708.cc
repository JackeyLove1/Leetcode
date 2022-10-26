#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}


inline int read() {
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

constexpr int N = 15;
char g[N][N][N];
bool st[N][N][N];
int k, n, m;

inline bool check(int a, int b, int c) {
    auto flag = a > 0 && b > 0 && c > 0 && a <= k && b <= n && c <= m;
    return flag && g[a][b][c] != '#' && !st[a][b][c];
}

constexpr int dirs[6][3] = {{1,  0,  0},
                            {-1, 0,  0},
                            {0,  1,  0},
                            {0,  -1, 0},
                            {0,  0,  1},
                            {0,  0,  -1}};

void dfs(int x, int y, int z, int &cnt) {
    if (check(x, y, z)) {
        ++cnt;
        st[x][y][z] = true;
        for (int i = 0; i < 6; ++i) {
            int dx = x + dirs[i][0];
            int dy = y + dirs[i][1];
            int dz = z + dirs[i][2];
            if (check(dx, dy, dz)) {
                dfs(dx, dy, dz, cnt);
            }
        }
    }
}

int main() {
    k = read(), n = read(), m = read();
    for (int a = 1; a <= k; ++a) {
        getchar();
        for (int b = 1; b <= n; ++b) {
            for (int c = 1; c <= m; ++c) {
                cin >> g[a][b][c];
            }
        }
    }
    int y = read(), z = read();
    int cnt = 0;
    dfs(1, y, z, cnt);
    cout << cnt << endl;
    return 0;
}