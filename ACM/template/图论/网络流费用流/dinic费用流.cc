#include <queue>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

const int N = 1e4 + 10, M = 1e5 + 10;

int n, m, S, T;
int idx = 1, head[N], nex[M], to[M], fl[M], w[M];

void addEdge(int u, int v, int f, int wi)
{
    nex[++idx] = head[u];
    head[u] = idx;
    to[idx] = v, fl[idx] = f, w[idx] = wi;
}
void addFlow(int u, int v, int f, int w)
{
    addEdge(u, v, f, w);
    addEdge(v, u, 0, -w);
}

namespace Dinic
{
    bool vis[N];
    int dis[N], now[N];

    bool SPFA(void) //用 SPFA 代替 BFS
    {
        std::queue<int> q;
        std::memset(dis, 0x3f, sizeof dis);
        std::memcpy(now, head, sizeof head);
        q.emplace(S);
        dis[S] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (int e = head[u]; e; e = nex[e])
                if (fl[e] && dis[to[e]] > dis[u] + w[e]) {
                    dis[to[e]] = dis[u] + w[e];
                    if (!vis[to[e]]) {
                        vis[to[e]] = 1;
                        q.emplace(to[e]);
                    }
                }
        }
        return dis[T] != 0x3f3f3f3f;
    }
    int dfs(int u, int flow, int &cost)
    {
        if (u == T) {
            cost += dis[T] * flow;
            return flow;
        }
        vis[u] = 1; //特判
        int rest = flow;
        for (int e = now[u]; rest && e; e = nex[e])
            if (fl[e] && dis[to[e]] == dis[u] + w[e] && !vis[to[e]]) { //还是这个特判，并且求的增广路必须同时是最短路
                now[u] = e;
                int tmp = dfs(to[e], std::min(fl[e], rest), cost);
                if (!tmp) dis[to[e]] = 0x3f3f3f3f;
                rest -= tmp;
                fl[e] -= tmp;
                fl[e ^ 1] += tmp;
            }
        vis[u] = 0;
        return flow - rest;
    }
    int main(int &res, int &cost)
    {
        while (SPFA())
            res += dfs(S, INT_MAX, cost);
        return 0;
    }
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

int main(void)
{
    std::cin >> n >> m >> S >> T;
    for (int i = 1; i <= m; ++i) {
        int u, v, f, w;
        std::cin >> u >> v >> f >> w;
        addFlow(u, v, f, w);
    }
    int res = 0, cost = 0;
    Dinic::main(res, cost);
    printf("%d %d\n", res, cost);
    return 0;
}
