#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <climits>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 1e5 + 100;
int n, m, w[N];
struct Node {
    int l, r;
    int v;
} tr[N * 4];

void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l]};
    } else {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].v;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        int v = INT_MIN;
        if (l <= mid) v = max(v, query(u << 1, l, r));
        if (r > mid) v = max(v, query(u << 1 | 1, l, r));
        return v;
    }
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    build(1, 1, n);
    int l, r;
    while (m--) {
        cin >> l >> r;
        cout << query(1, l, r) << endl;
    }
    return 0;
}