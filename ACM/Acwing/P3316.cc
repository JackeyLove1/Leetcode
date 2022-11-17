#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
char s[N], t[N];
int ne[N];

int main() {
    // fhj();
    scanf("%s%s", t + 1, s + 1);
    const int n = std::strlen(s + 1), m = std::strlen(t + 1);
    memset(ne, 0, sizeof ne);
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) ++j;
        ne[i] = j;
    }
    for (int i = 1, j = 0; i <= m; ++i) {
        while (j && t[i] != s[j + 1]) j = ne[j];
        if (t[i] == s[j + 1]) ++j;
        if (j == n) {
            cout << i - n + 1 << endl;
            j = ne[j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ne[i] << " ";
    }
    return 0;
}