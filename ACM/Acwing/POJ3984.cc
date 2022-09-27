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
// #include <array>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 5, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
int g[N+1][N+1];
bool vis[N+1][N+1];
PII pre[N+1][N+1];
inline int bfs(){
    memset(vis, false, sizeof vis);
    queue<PII> q;
    q.push({1, 1});
    pre[1][1] = {-1, -1};
    int cnt = 0;
    while(!q.empty()){
        ++cnt;
        auto t = q.front();
        q.pop();
        auto x = t.first, y = t.second;
        vis[x][y] = true;
        for (int i = 0; i < 2 ; ++i){
            for (int j = 0; j < 2; ++j){
                if (i == 1 && j == 1) continue;
                auto x0 = x + i, y0 = y + j;
                // cout <<"x0: " << x0 <<" y0: " << y0 << endl;
                // cout <<"vis[x0][y0]: " << vis[x0][y0]<<" g[x0][y0]: " << g[x0][y0] << endl;
                if (x0 <= N && y0 <= N){
                    if (!vis[x0][y0] && !g[x0][y0]){
                     q.push({x0, y0});
                     pre[x0][y0] = {x, y};
                     // cout <<"x0: " << x0 <<" y0: " << y0 << endl;
                     if (x0 == N && y0 == N) return cnt;
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
    for (int i = 1; i <= N; ++i){
        for (int  j = 1; j <= N; ++j){
            cin >> g[i][j];
        }
    }
    bfs();
    vector<PII> res;
    PII end = {N, N};
    while( end.first != -1 && end.second != -1){
        res.push_back(end);
        end = pre[end.first][end.second];
    }
    reverse(res.begin(), res.end());
    for (const auto& v : res){
        cout << "(" << v.first -1  <<", " << v.second-1 <<")"<<endl;
    }
    return 0;
}