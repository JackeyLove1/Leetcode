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

int main() {
    fhj();
    int K;
    cin >> K;
    while (K--) {
        init();
        cin >> n >> m;
        // m: num, h: n + num
        string s1, s2;
        while (m--) {
            cin >> s1 >> s2;
            int u = std::stoi(s1.substr(1)), v = std::stoi(s2.substr(1));
            // cout << "u:" << u << " v:" << v << endl;
            int type1 = (s1[0] == 'm') ? 0 : 1, type2 = (s2[0] == 'm') ? 0 : 1;
            add((1 - type1) * n + u, type2 * n + v);
            add((1 - type2) * n + v, type1 * n + u);
            /*
            if (s1[0] == 'm' && s2[0] == 'm') {
                add(u + n, v), add(v + n, u);
            }
            if (s1[0] == 'm' && s2[0] == 'h') {
                add(u + n, v + n), add(v, u);
            }
            if (s1[0] == 'h' && s2[0] == 'h') {
                add(u, v + n), add(v, u + n);
            }
            if (s1[0] == 'h' && s2[0] == 'm') {
                add(u, v), add(v + n, u + n);
            }
             */
        }
        for (int i = 1; i <= n * 2; i++) {
            if (!dfn[i]) tarjan(i);
        }
        bool flag = true;
        for (int i = 1; i <= n && flag; i++)
            if (id[i] == id[i + n]) {
                cout << "BAD" << endl;
                flag = false;
            }
        if (flag) cout << "GOOD" << endl;
    }
    return 0;
}
