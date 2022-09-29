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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 20, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
constexpr int dx[]{1, 0, -1, 0}, dy[]{0, 1, 0, -1};
constexpr int sz = sizeof dx / sizeof dx[0];
int n, m;

char g[N][N];
bool col[N], dg[N], udg[N];

void dfs(int u, int &cnt) {
    if (u == n) {
        ++cnt;
        return;
    }

    for (int i = 0; i < n; i++)
        if (!col[i] && !dg[u + i] && !udg[n - u + i]) {
            col[i] = dg[u + i] = udg[n - u + i] = true;
            dfs(u + 1, cnt);
            col[i] = dg[u + i] = udg[n - u + i] = false;
        }
}

int main() {
    /*
    const int vec[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v;
    for (int i = 1; i <= 10; ++i) {
        n = i;
        memset(col, 0, sizeof col);
        memset(udg, 0, sizeof udg);
        memset(dg, 0, sizeof dg);
        int cnt = 0;
        dfs(0, cnt);
        v.push_back(cnt);
    }
    for (auto num: v) { cout << num << ","; }
     */
    const int res[] {0,1,0,0,2,10,4,40,92,352,724};
    while (cin >> n && n){
        cout << res[n] << endl;
    }
    return 0;
}
