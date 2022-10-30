#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

template<typename T>
inline T read() {
    T ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}
using ll = long long;
#define ri read<int>()
#define rl read<ll>()
constexpr int N = 1e6 + 100;
int e[N], ne[N], w[N], h[N], idx, f[N];
inline void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

int dfs(int fa, int u) {
    int res = 0;
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        res = std::max(res, dfs(u, j) + w[i]);
    }
    return res;
}

int main() {
    memset(h, -1, sizeof h);
    int n = read<int>();
    ll res = 0;
    for(int i = 1; i < n; ++i){
        int a = ri, b = ri, c = ri;
        add(a, b, c);
        res += 2 * c;
    }
    cout << res - dfs(-1, 1) << endl;
    return 0;
}