#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 110;
constexpr int mod = 1e9 + 7;
int a[N];
int n;
int tree[N];

inline int lowbit(int x) {
    return x & (-x);
}

//树的维护
void update(int x, int k) {
    for (; x <= n; x += lowbit(x))
        tree[x] += k;
}

//查询
ll query(int x) {
    ll ans = 0;
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

//求和
inline ll unite(int x, int y) {
    return query(x) - query(y - 1);
}

int main() {
    fhj();
    cin >> n;
    memset(tree, 0, sizeof tree);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ++a[i];
        update(a[i], 1);
        cout << query(a[i] - 1) << endl;
    }
    return 0;
}