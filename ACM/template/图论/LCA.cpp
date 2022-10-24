#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 40010, M = N * 2;

int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][16];
int q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs(int root)
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1; // 一定要注意depth[0] = 0
    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                q[ ++ tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 15; k ++ )
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k -- )
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 15; k >= 0; k -- )
        if (fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

int main()
{
    scanf("%d", &n);
    int root = 0;
    memset(h, -1, sizeof h);

    for (int i = 0; i < n; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1) root = a;
        else add(a, b), add(b, a);
    }

    bfs(root);

    scanf("%d", &m);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if (p == a) puts("1");
        else if (p == b) puts("2");
        else puts("0");
    }

    return 0;
}

/*
#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100, K = 21;
int h[N], ne[N], e[N], idx;
int fa[N][K + 1], depth[N];
int n, m, root;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void bfs(int s) {
    memset(depth, 0x3f, sizeof depth);
    memset(fa, 0, sizeof fa);
    queue<int> q;
    q.push(s);
    depth[0] = 0, depth[s] = 1;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q.push(j);
                fa[j][0] = t;
                for (int k = 1; k <= K; ++k) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                    // cout << "j: " << j <<" k: " << k <<" f[j][k]: " << fa[j][k] << endl;
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) std::swap(a, b);
    for (int k = K; k >= 0; --k) {
        if (depth[fa[a][k]] >= depth[b]) {
            a = fa[a][k];
        }
    }
    if (a == b) return a;
    for (int k = K; k >= 0; --k) {
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k], b = fa[b][k];
        }
    }
    return fa[a][0];
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    cin >> n >> m >> root;
    int a, b;
    for (int i = 1; i < n; ++i) {
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    bfs(root);
    while (m--) {
        cin >> a >> b;
        // cout << "a: " << depth[a] << " b: " << depth[b] << endl;
        cout << lca(a, b) << endl;
    }
    return 0;
}
*/