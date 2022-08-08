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

constexpr int N = 2e5 + 100, M = 1e6 + 100, INF = 0x3f3f3f3f;

int n, m;
int h[M], e[M], ne[M], w[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int d[N];
bool st[N];

void dfs(int u, bool &flag) {
    st[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            if (d[j] != 2) {
                flag = false;
                // return;
            }
            dfs(j, flag);
        }
    }
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    int a, b;
    while (m--) {
        cin >> a >> b;
        add(a, b, 1);
        add(b, a, 1);
        ++d[a], ++d[b];
    }
    int res = 0;
    bool flag = true;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == 2 && !st[i]) {
            flag = true;
            dfs(i, flag);
            if (flag) ++res;
        }
    }
    cout << res << endl;
    return 0;
}