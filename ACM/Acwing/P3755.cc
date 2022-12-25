#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 500010;

int n, m;
using ll = long long;

struct Data {
    int a, b, c, p, id, sign;
    ll sum;

    const bool operator<(const Data &rhs) const {
        if (a != rhs.a) return a < rhs.a;
        if (b != rhs.b) return b < rhs.b;
        return c < rhs.c;
    }

    const bool operator==(const Data &rhs) const {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }
} q[N], w[N];

ll ans[N];

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid), merge_sort(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    ll sum = 0;
    while (i <= mid && j <= r) {
        if (q[i].b <= q[j].b) sum += (!q[i].c) * q[i].p, w[k++] = q[i++];
        else q[j].sum += sum, w[k++] = q[j++];
    }
    while (i <= mid) sum += (!q[i].c) * q[i].p, w[k++] = q[i++];
    while (j <= r) q[j].sum += sum, w[k++] = q[j++];
    for (i = l, j = 0; j < k; ++i, ++j) q[i] = w[j];
}

int main() {
    fhj();
    cin >> n >> m;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int a, b, p;
        cin >> a >> b >> p;
        q[k++] = {a, b, 0, p, 0, 1};
    }
    for (int i = 1; i <= m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        q[k++] = {x2, y2, 1, 0, i, 1};
        q[k++] = {x1 - 1, y2, 1, 0, i, -1};
        q[k++] = {x2, y1 - 1, 1, 0, i, -1};
        q[k++] = {x1 - 1, y1 - 1, 1, 0, i, 1};
    }
    sort(q, q + k);
    merge_sort(0, k - 1);
    for (int i = 0; i < k; ++i) {
        if (q[i].id) {
            ans[q[i].id] += q[i].sum * q[i].sign;
        }
    }
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}