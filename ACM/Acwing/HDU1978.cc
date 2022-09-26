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
#include <unordered_map>
#include <unordered_set>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 110, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
constexpr auto P = 131;
int g[N][N], f[N][N];
int n, m;

inline bool check(int x, int y){
    if (x < 1 || x > n || y < 1 || y > m)
        return false;
    return true;
}

int dfs(int x, int y){
    int& ret = f[x][y];
    if (ret != -1) return ret;
    ret = 0;
    for (int i = 0; i <= g[x][y]; ++i){
        for (int j = 0; j <= g[x][y] - i; ++j){
            auto x0 = x + i, y0 = y + j;
            if (check(x0, y0)){
                ret = (ret + dfs(x0, y0)) % MOD;
            }
        }
    }
    return ret;
}

inline void solve(){
    cin >> n >> m;
    memset(f, -1, sizeof f);
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            cin >> g[i][j];
        }
    }
    f[n][m] = 1;
    cout << dfs(1, 1) << endl;
}

int main(){
    fhj();
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}