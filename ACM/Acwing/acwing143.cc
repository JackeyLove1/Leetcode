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
int son[N][2], nums[N];
int idx;
char str[N];

inline void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int &s = son[p][x >> i & 1];
        if (!s) s = ++idx;
        p = s;
    }
}

inline int search(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int s = x >> i & 1;
        if (son[p][!s]) {
            res += 1 << i;
            p = son[p][!s];
        } else p = son[p][s];
    }
    return res;
}

int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) {
        nums[i] = read();
        insert(nums[i]);
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = std::max(res, search(nums[i]));
    }
    cout << res << endl;
    return 0;
}