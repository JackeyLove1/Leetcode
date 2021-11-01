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

constexpr int N = 1e6 + 100;

struct Node {
    int l, r;
    int v;
} tr[N * 4];

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int v = 0, mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}

void modify(int u, int x, int v) {
    if (tr[u].l == tr[u].r) tr[u].v = v;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }
}

int m, p;
using ll = long long;

int main() {
    fhj();
    int n = 0, last = 0;
    cin >> m >> p;
    build(1, 1, m);
    while (m--) {
        char op;
        cin >> op;
        if (op == 'A') {
            int t;
            cin >> t;
            modify(1, n + 1, ((ll) t + last) % p);
            ++n;
        } else {
            int L;
            cin >> L;
            last = query(1, n - L + 1, n);
            cout << last << endl;
        }
    }
    return 0;
}

