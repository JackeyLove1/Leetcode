#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2000010;
using ll = long long;
int tot = 1, last = 1;
struct Node {
    int len, fa;
    int ch[26];
} node[N];
char str[N];
ll f[N], ans;
int h[N], e[N], ne[N], idx;

inline void extend(int c) {
    int p = last, np = last = ++tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else {
            int nq = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    for (int i = h[u]; ~i; i = ne[i]) {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
    if (f[u] > 1) ans = max(ans, f[u] * node[u].len);
}

int main() {
    fhj();
    int n;
    cin >> n;
    vector<string> strs;
    string ss;
    for (int i = 0; i < n; ++i) {
        cin >> ss;
        strs.emplace_back(ss);
    }
    scanf("%s", str);
    for (int i = 0; str[i]; i++) extend(str[i] - 'a');
    int res = 0;
    for (const auto &s: strs) {
        int p = 1, i = 0;
        for (; i < s.size(); ++i) {
            if (!node[p].ch[s[i] - 'a']) break;
            p = node[p].ch[s[i] - 'a'];
        }
        // cout << "s: " << s << " i: " << i << endl;
        res += i == s.size();
    }
    cout << res << endl;
    return 0;
}