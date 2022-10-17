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
#include <deque>
#include <functional>
#include <tuple>
#include <array>
#include <iomanip>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

using namespace std;

constexpr int N = 1e5 + 100, M = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], cnt[M], dist[N], idx;
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<>> q;
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (st[u]) continue;
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
    }
}

// SLF优化spfa
void spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    deque<int> q;
    q.push_back(s), dist[s] = 0;
    while (!q.empty()) {
        auto t = q.front();
        st[t] = false;
        q.pop_front();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    if (!q.empty() && dist[q.front()] > dist[j]) {
                        q.push_front(j);
                    } else {
                        q.push_back(j);
                    }
                    st[j] = true;
                }
            }
        }
    }
}

int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, Size[N];
int din[N], dout[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = std::min(low[u], low[j]);
        }else if(in_stk[j]) low[u] = std::min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        int y;
        ++scc_cnt;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            ++Size[scc_cnt];
        } while (y != u);
    }
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--){
        int a, b;
        cin >> a >> b;
        add(a, b, 1);
    }
    for(int i = 1; i <= n; ++i){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    // topsort
    for(int i = 1; i <= n; ++i){
        for(int j = h[i]; j != -1; j = ne[j]){
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b){
                dout[a]++;
            }
        }
    }
    int res = 0, zero = 0;
    for(int i = 1; i <= scc_cnt; ++i){
        if (!dout[i]){
            res += Size[i];
            if (++zero > 1){
                res = 0;
                break;
            }
        }
    }
    cout << res << endl;
    return 0;
}
