#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}


constexpr int N = 2e7 + 100;
using ll = long long;
int tot = 1, last = 1;
struct Node {
    int len, fa;
    int ch[4];
} node[N];
string str;
ll f[N];

inline int get(char c) {
    switch (c) {
        case 'E':
            return 0;
        case 'S':
            return 1;
        case 'N':
            return 2;
        default:
            return 3;
    }
}

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


int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    cin >> str;
    for (size_t i = 0; i < str.size(); ++i) extend(get(str[i]));
    string t;
    while (m--) {
        cin >> t;
        int p = 1, res = 0;
        for (size_t i = 0; i < t.size(); ++i) {
            int u = node[p].ch[get(t[i])];
            if (!u) break;
            p = u;
            ++res;
        }
        cout << res << endl;
    }
    return 0;
}