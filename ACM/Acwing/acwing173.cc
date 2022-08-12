#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f;
int f[N][N];
char g[N][N];
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    queue<PII> q;
    memset(f, -1, sizeof f);
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
        for(int j = 0; j < m; ++j){
            if (g[i][j] == '1'){
                q.emplace(i, j);
                f[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= n || ny >= m || nx < 0 || ny < 0) continue;
            if (f[nx][ny] == -1){
                f[nx][ny] = f[x][y] + 1;
                q.emplace(nx, ny);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << f[i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}