#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1010, M = 20010, INF = 1e8;

int n, m, S, T;
ll h[N], e[M], f[M], ne[M], idx;
ll q[N], d[N], pre[N];
bool st[N];

// 数组d表示当前所有边上的容量最小值
// pre前驱节点
// 在残差网络中不断使用BFS寻找增广路，直到找不到
// 就构成了最大流

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
    // 残差网络，容量图
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
    // 反向图
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(st, false, sizeof st);
    q[0] = S, st[S] = true, d[S] = INF;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (!st[ver] && f[i])
                // 如果这个点被遍历过就不需要遍历
            {
                st[ver] = true;
                d[ver] = std::min(d[t], f[i]);
                // 记录一下前驱边
                pre[ver] = i;
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

ll EK() {
    ll r = 0;
    while (bfs()) {
        r += d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
            // 维护容量网络里的残差网络和反图容量
            f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
    }
    return r;
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读


int main() {
    int x;
    n = read(), m = read(), x = read();
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }
    S = 1, T = n;
    auto res = EK();
    if (res) cout << res << " " << static_cast<ll>((res + x - 1) / res) << endl;
    else cout << "Orz Ni Jinan Saint Cow!" << endl;
    return 0;
}

