#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

template<typename T = int>
inline T read() {
    T ans = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            sgn *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * sgn;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2000100, INF = 1e8;
int n, m, S, T;
std::array<int, N> h{}, e{}, f{}, ne{}, d{}, cur{};
int idx{0};

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() {
    queue<int> q;
    d.fill(-1);
    q.push(S), d[S] = 0, cur[S] = h[S];
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q.push(ver);
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) {
            int t = find(ver, std::min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) {
        while (flow = find(S, INF), flow != 0) r += flow;
    }
    return r;
}

int main() {
    n = read(), S = 0, T = n + 1;
    int sum = 0, cnt = T;
    for (int i = 1; i <= n; i++) {
        int x = read();
        add(S, i, x);
        sum += x;
    }
    for (int i = 1; i <= n; i++) {
        int x = read();
        add(i, T, x);
        sum += x;
    }
    m = read();
    for (int i = 0; i < m; ++i) {
        int k = read(), c1 = read(), c2 = read();
        add(S, ++cnt, c1);
        add(++cnt, T, c2);
        sum += c1;
        sum += c2;
        while (k--) {
            int c = read();
            add(cnt - 1, c, INF);
            add(c, cnt, INF);
        }
    }
    cout << sum - dinic() << endl;
    return 0;
}