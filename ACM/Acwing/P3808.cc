#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
int ch[N][30], cnt[N], ne[N], idx{0};
int n, m;

inline void insert(char *s) {
    int p = 0;
    for (int i = 0; s[i]; ++i) {
        int j = s[i] - 'a';
        if (!ch[p][j]) ch[p][j] = ++idx;
        p = ch[p][j];
    }
    ++cnt[p];
}

inline void build() {
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (ch[0][i]) q.push(ch[0][i]);
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i){
            int v = ch[u][i];
            if (v) ne[v] = ch[ne[u]][i], q.push(v);
            else ch[u][i] = ch[ne[u]][i];
        }
    }
}

inline int query(char *s) {
    int res = 0;
    for (int k = 0, p = 0; s[k]; ++k) {
        p = ch[p][s[k] - 'a'];
        for (int j = p; j && ~cnt[j]; j = ne[j]) {
            res += cnt[j], cnt[j] = -1;
        }
    }
    return res;
}

char s[N];

int main() {
    // fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    build();
    scanf("%s", s);
    cout << query(s) << endl;
    return 0;
}