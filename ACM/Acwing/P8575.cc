#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 4e5 + 100, M = 2e5 + 100;
int n, m;
int e[N], h[N], ne[N], idx;
int L[N], R[N], dep[N], tot;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

struct Data {
    int red, blue, dfn, sz, id, res;

    bool operator<(const Data &t) const {
        if (red != t.red) return red < t.red;
        if (blue != t.blue) return blue < t.blue;
        return dfn > t.dfn;
    }

    bool operator==(const Data &t) const {
        return red == t.red && blue == t.blue && dfn == t.dfn;
    }
} q[N], w[N];

int ans[N], tr[M];

inline int lowbit(int x) {
    return x & -x;
}

inline void update(int x, int v) {
    for (int i = x; i < M; i += lowbit(i)) tr[i] += v;
}

inline int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid), merge_sort(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
        if (q[i].blue <= q[j].blue) update(q[i].dfn, 1), w[k++] = q[i++];
        else q[j].res += query(q[j].dfn + q[j].sz - 1) - query(q[j].dfn), w[k++] = q[j++];
    while (i <= mid) update(q[i].dfn, 1), w[k++] = q[i++];
    while (j <= r) q[j].res += query(q[j].dfn + q[j].sz - 1) - query(q[j].dfn), w[k++] = q[j++];
    for (i = l; i <= mid; i++) update(q[i].dfn, -1);
    for (i = l, j = 0; j < k; i++, j++) q[i] = w[j];
}

void dfs(int u, int fa) {
    q[u].dfn = ++tot;
    q[u].sz = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int nxt = e[i];
        if (nxt == fa) continue;
        dfs(nxt, u);
        q[u].sz += q[nxt].sz;
    }
}

int main() {
    fhj();
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    for (int i = 1; i <= n; ++i) {
        int red, blue;
        cin >> red >> blue;
        q[i] = {red, blue, 0, 0, i, 0};
    }
    dfs(1, -1);
    sort(q + 1, q + n + 1);
    merge_sort(1, n);
    for (int i = 1; i <= n; ++i) {
        if (q[i].res) {
            ans[q[i].id] = q[i].res;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (ans[i]) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}