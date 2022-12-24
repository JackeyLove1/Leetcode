// 权值线段树套区间线段树
// 权值线段树维护 权值-下标映射
// 区间线段树维护 区间-权值映射
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 50010, P = N * 17 * 17, M = N * 4;
int n, m;
struct Tree {
    int lson, rson, sum, add;
} tr[P];                   // 区间线段树
int L[M], R[M], T[M], idx; // 权值线段树
struct Query {
    int op, a, b, c;
} q[N];
vector<int> nums;

inline int get(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

inline void pushup(int u) { tr[u].sum = tr[tr[u].lson].sum + tr[tr[u].rson].sum; }

void build(int u, int l, int r) {
    L[u] = l, R[u] = r, T[u] = ++idx;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

inline int intersection(int a, int b, int c, int d) {
    return std::min(b, d) - std::max(a, c) + 1;
}

void updatePart(int u, int l, int r, int ql, int qr) {
    tr[u].sum += intersection(l, r, ql, qr);
    if (ql <= l && r <= qr) {
        tr[u].add++;
        return;
    }
    int mid = l + r >> 1;
    if (ql <= mid) {
        if (!tr[u].lson) tr[u].lson = ++idx;
        updatePart(tr[u].lson, l, mid, ql, qr);
    }
    if (qr > mid) {
        if (!tr[u].rson) tr[u].rson = ++idx;
        updatePart(tr[u].rson, mid + 1, r, ql, qr);
    }
}

// 第 a 个位置到第 b 个位置的权值线段树，每个位置加入一个数 c
void change(int u, int a, int b, int c) {
    updatePart(T[u], 1, n, a, b);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (c > mid) change(u << 1 | 1, a, b, c);
    else change(u << 1, a, b, c);
}

int queryPartSum(int u, int l, int r, int ql, int qr, int add) {
    if (ql <= l && r <= qr) return tr[u].sum + add * (r - l + 1);
    int mid = l + r >> 1;
    int res = 0;
    add += tr[u].add;
    if (ql <= mid) {
        if (tr[u].lson) res += queryPartSum(tr[u].lson, l, mid, ql, qr, add);
        else res += intersection(l, mid, ql, qr) * add;
    }
    if (qr > mid) {
        if (tr[u].rson) res += queryPartSum(tr[u].rson, mid + 1, r, ql, qr, add);
        else res += intersection(mid + 1, r, ql, qr) * add;
    }
    return res;
}

int query(int u, int a, int b, int c) {
    if (L[u] == R[u]) return L[u];
    int k = queryPartSum(T[u << 1 | 1], 1, n, a, b, 0);
    if (k >= c) return query(u << 1 | 1, a, b, c);
    else return query(u << 1, a, b, c - k);
}

int main() {
    fhj();
    cin >> n >> m;
    memset(T, 0, sizeof T), memset(L, 0, sizeof L), memset(R, 0, sizeof R);
    nums.reserve(n);
    for (int i = 0; i < m; ++i) {
        cin >> q[i].op >> q[i].a >> q[i].b >> q[i].c;
        if (q[i].op == 1) {
            nums.push_back(q[i].c);
        }
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    build(1, 0, nums.size() - 1);
    for (int i = 0; i < m; ++i) {
        if (q[i].op == 1) {
            change(1, q[i].a, q[i].b, get(q[i].c));
        } else {
            cout << nums[query(1, q[i].a, q[i].b, q[i].c)] << endl;
        }
    }
    return 0;
}