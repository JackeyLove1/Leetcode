#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N = 4e4 + 5, M = 1e6 + 5;
int n1, n2, n3, m, tot = 1, lnk[N], ter[M], nxt[M], val[M], dep[N], cnr[N];

inline int id(int p, int x) {
    switch (p) {
        case 1:
            return x;
        case 2:
            return n2 + x;
        case 3:
            return n2 + n1 + x;
        case 4:
            return n2 + n1 + n1 + x;
    }
}

void add(int u, int v, int w) {
    ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, val[tot] = w;
}

void addedge(int u, int v, int w) {
    add(u, v, w), add(v, u, 0);
}

int bfs(int s, int t) {
    memset(dep, 0, sizeof(dep));
    memcpy(cnr, lnk, sizeof(lnk));
    std::queue<int> q;
    q.push(s), dep[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = lnk[u]; i; i = nxt[i]) {
            int v = ter[i];
            if (!dep[v] && val[i]) dep[v] = dep[u] + 1, q.push(v);
        }
    }
    return dep[t];
}

int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    int ans = 0;
    for (int i = cnr[u]; i && ans < flow; i = nxt[i]) {
        cnr[u] = i;
        int v = ter[i];
        if (val[i] && dep[v] == dep[u] + 1) {
            int x = dfs(v, t, std::min(val[i], flow - ans));
            if (x) val[i] -= x, val[i ^ 1] += x, ans += x;
        }
    }
    if (ans < flow) dep[u] = -1;
    return ans;
}

int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        int x;
        while ((x = dfs(s, t, 1 << 30))) ans += x;
    }
    return ans;
}

int main() {
    scanf("%d%d%d", &n1, &n2, &n3);
    int v;
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            scanf("%d", &v);
            if (v) addedge(id(1, j), id(2, i), 1);
        }
    }
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n3; ++j) {
            scanf("%d", &v);
            if (v)addedge(id(3, i), id(4, j), 1);
        }
    }
    for (int i = 1; i <= n1; ++i) addedge(id(2, i), id(3, i), 1);
    int S = 0, T = n2 + n1 + n1 + n3 + 1;
    for (int i = 1; i <= n2; ++i) addedge(S, id(1, i), 1);
    for (int i = 1; i <= n3; ++i) addedge(id(4, i), T, 1);
    printf("%d\n", dinic(S, T));
    return 0;
}