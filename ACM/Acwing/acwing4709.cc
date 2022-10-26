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
using ll = long long;
int tr[N], ans[N];
int n;

inline int lowbit(int x) {
    return x & -x;
}

inline void insert(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += v;
}

inline int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

inline ll cal(int x) {
    return x >= 2 ? (1l * x * (x - 1) / 2) : 0;
}

std::array<int, N> a, f, l, r;
std::vector<int> nums;
const bool Debug = true;

inline int find(int x) {
    return std::lower_bound(nums.begin(), nums.end(), x) - nums.begin() + 1;
}

int main() {
    n = read();
    nums.reserve(n);
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        nums.push_back(a[i]);
    }
    sort(nums.begin(), nums.end());
    for (int i = 1; i <= n; ++i) a[i] = find(a[i]);
    ll res = 0;
    // 以i为中点构造三元祖
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1 - query(a[i]);
        insert(a[i], 1);
    }
    memset(tr, 0, sizeof tr);
    for (int i = n; i >= 1; --i) {
        r[i] = query(a[i]);
        insert(a[i], 1);
    }
    for (int i = 1; i <= n; ++i) {
        res += 1ll * l[i] * r[i];
    }
    cout << res << endl;
    return 0;
}