#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

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

constexpr int N = 500010;

int n, m, w[N];
struct Node {
    int l, r;
    int sum, tmax;
    int lmax, rmax;
} tr[N * 4];

void pushup(Node &u, Node &l, Node &r) {
    u.sum = l.sum + r.sum;
    u.lmax = max(l.lmax, l.sum + r.lmax);
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.tmax = max({l.tmax, r.tmax, l.rmax + r.lmax});
}

void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    if (l == r) {
        tr[u].sum = w[l], tr[u].lmax = w[l];
        tr[u].rmax = w[l], tr[u].tmax = w[l];
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) {
        tr[u].sum = v, tr[u].tmax = v;
        tr[u].lmax = v, tr[u].rmax = v;
        // pushup(u);
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

Node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (mid >= r) return query(u << 1, l, r);
        else if (mid < l) return query(u << 1 | 1, l, r);
        else {
            Node res;
            Node left = query(u << 1, l, r);
            Node right = query(u << 1 | 1, l, r);
            pushup(res, left, right);
            return res;
        }
    }
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    build(1, 1, n);
    while (m--) {
        int k, x, y;
        cin >> k >> x >> y;
        if (k == 1) {
            if (x > y) swap(x, y);
            auto res = query(1, x, y);
            cout << res.tmax << endl;
        } else {
            modify(1, x, y);
        }
    }
    return 0;
}