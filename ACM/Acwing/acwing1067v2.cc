#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 5510, INF = 1e9;
int n, m;
int l[N], r[N], u[N], d[N], s[N], row[N], col[N], idx;
int ans[N], top;


void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        s[i] = 0;
        d[i] = u[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

void add(int &hh, int &tt, int x, int y) {
    row[idx] = x, col[idx] = y, s[y]++;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx++;
}

void remove(int p) {
    r[l[p]] = r[p], l[r[p]] = l[p];
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j]) {
            s[col[j]]--;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}

void resume(int p) {
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]]++;
        }
    r[l[p]] = p, l[r[p]] = p;
}

bool dfs() {
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = d[p]; i != p; i = d[i]) {
        ans[++top] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top--;
    }
    resume(p);
    return false;
}

int main() {
    fhj();
    cin >> n >> m;
    init();
    for (int i = 1; i <= n; ++i) {
        int hh = idx, tt = idx;
        for (int j = 1; j <= m; ++j) {
            int x;
            cin >> x;
            if (x) add(hh, tt, i, j);
        }
    }
    if (dfs()) {
        for (int i = 1; i <= top; ++i) {
            cout << ans[i] << " ";
        }
    } else {
        cout << "No Solution!" << endl;
    }
    return 0;
}