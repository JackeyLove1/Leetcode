#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

constexpr int N = 2010, M = 4000010;

int n;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];

struct Wedding {
    int s, t, d;
} w[N];

bool is_overlap(int a, int b, int c, int d) {
    return d > a && b > c;
}

void add(int a, int b) {
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
    if (dfn[u] == low[u]) {
        int y;
        cnt++;
        do {
            y = stk[top--], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h), idx = 0;
    for (int i = 0; i < n; i++) {
        int s0, s1, t0, t1, d;
        scanf("%d:%d %d:%d %d", &s0, &s1, &t0, &t1, &d);
        w[i] = {s0 * 60 + s1, t0 * 60 + t1, d};
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) {
            auto a = w[i], b = w[j];
            if (is_overlap(a.s, a.s + a.d, b.s, b.s + b.d)) add(i, j + n), add(j, i + n);
            if (is_overlap(a.s, a.s + a.d, b.t - b.d, b.t)) add(i, j), add(j + n, i + n);
            if (is_overlap(a.t - a.d, a.t, b.s, b.s + b.d)) add(i + n, j + n), add(j, i);
            if (is_overlap(a.t - a.d, a.t, b.t - b.d, b.t)) add(i + n, j), add(j + n, i);
        }


    for (int i = 0; i < n * 2; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 0; i < n; i++)
        if (id[i] == id[i + n]) {
            puts("NO");
            return 0;
        }

    puts("YES");
    for (int i = 0; i < n; i++) {
        auto a = w[i];
        int s = a.s, t = a.t, d = a.d;
        if (id[i] < id[i + n])
            printf("%02d:%02d %02d:%02d\n", s / 60, s % 60, (s + d) / 60, (s + d) % 60);
        else
            printf("%02d:%02d %02d:%02d\n", (t - d) / 60, (t - d) % 60, t / 60, t % 60);
    }

    return 0;
}