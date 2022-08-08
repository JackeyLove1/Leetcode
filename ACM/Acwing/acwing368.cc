#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
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

constexpr int N = 100010, M = 600010, INF = 0x3f3f3f3f;
int n, m;
int h[N], hs[N], e[M], ne[M], w[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];
int dist[N];

static inline void add(int h[], int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (y != u);
    }
}

bool st[N];

void spfa(int start, int times) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[start] = 0;
    st[start] = true;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        st[t] = false;
        for (int i = hs[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    cin >> n >> m;
    int a, b, t;
    for (int i = 0; i < m; ++i) {
        cin >> t >> a >> b;
        if (t == 1) add(h, a, b, 0), add(h, b, a, 0);
        else if (t == 2) add(h, a, b, 1);
        else if (t == 3) add(h, b, a, 0);
        else if (t == 4) add(h, b, a, 1);
        else add(h, a, b, 0);
    }
    for (int i = 1; i <= n; ++i) {
        add(h, 0, i, 1);
    }
    tarjan(0);
    // build new DAG
    bool flag = true;
    for (int i = 0; i <= n && flag; ++i) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            a = id[i], b = id[k];
            if (a == b) {
                if (w[j] > 0) {
                    flag = false;
                    break;
                }
            }
            else add(hs, a, b, w[j]);
        }
    }
    if (!flag) {
        cout << -1 << endl;
        return 0;
    }
    ll res = 0;
    // spfa(0, n);
    for (int i = scc_cnt; i; i -- )
    {
        for (int j = hs[i]; ~j; j = ne[j])
        {
            int k = e[j];
            dist[k] = max(dist[k], dist[i] + w[j]);
        }
    }
    for (int i = 1; i <= scc_cnt; ++i) {
        // cout << "i: " << i << " dist: " << dist[i] << endl;
        res += static_cast<ll>(scc_size[i]) * dist[i];
    }
    cout << res << endl;
    return 0;
}