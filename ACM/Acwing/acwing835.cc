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

constexpr int N = 1e6 + 100;
int son[N][26], cnt[N];
int idx;

inline void insert(const string &s) {
    int p = 0;
    for (int i = 0; i < s.size(); ++i) {
        int u = s[i] - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    ++cnt[p];
}

inline int query(const string &s) {
    int p = 0;
    for (int i = 0; i < s.size(); ++i) {
        int u = s[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main() {
    fhj();
    int n;
    string op, s;
    cin >> n;
    while (n--) {
        cin >> op >> s;
        if (op == "I") {
            insert(s);
        } else {
            cout << query(s) << endl;
        }
    }
    return 0;
}