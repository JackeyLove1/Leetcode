#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

constexpr int N = 1e5 + 100;
int son[N][26], cnt[N];
int idx;
char str[N];

inline void insert(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++;
}

inline int query(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main() {
    fhj();
    string s;
    unordered_map<string, int> mp;
    int n;
    cin >> n;
    mp.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        mp[s] = 1;
    }
    int m;
    cin >> m;
    while (m--) {
        cin >> s;
        auto &v = mp[s];
        if (v == 0) {
            cout << "WRONG" << endl;
        } else if (v == 1) {
            cout << "OK" << endl;
            ++v;
        } else {
            cout << "REPEAT" << endl;
        }

    }
    return 0;
}