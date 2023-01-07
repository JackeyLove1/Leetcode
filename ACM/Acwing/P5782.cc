#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2000010, M = 2000010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline void init() {
    ts = 0, top = 0, cnt = 0, idx = 0;
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(ins, 0, sizeof ins);
    memset(id, 0, sizeof id);
    memset(stk, 0, sizeof stk);
}

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    stk[++top] = u, ins[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (ins[j]) low[u] = min(low[u], dfn[j]);
    }

    if (low[u] == dfn[u]) {
        int y;
        cnt++;
        do {
            y = stk[top--], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

inline int rev(int x) {
    return (x % 2) ? x + 1 : x - 1;
}

int main() {
    memset(h, -1, sizeof h);
    n = read(), m = read();
    while (m--) {
        int a = read(), b = read();
        // add(rev(a), b), add(rev(b), a);
        add(a, rev(b)), add(b, rev(a));
    }
    for (int i = 1; i <= n * 2; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n * 2; i += 2) {
        if (id[i] == id[rev(i)]) {
            cout << "NIE" << endl;
            return 0;
        }
    }
    for (int i = 1; i <= n * 2; i += 2) {
        if (id[i] < id[rev(i)]) {
            cout << i << endl;
        } else {
            cout << rev(i) << endl;
        }
    }
    return 0;
}