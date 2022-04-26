#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

static inline int cnt_(int x) {
    return __builtin_popcount(x);
}

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 100010, M = 3100010;

int n, m;
int a[N];
vector<int> nums;
struct Node {
    int l, r, cnt;
} tr[N * 4 + N * 17];
int root[N], idx;

int find(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

int build(int l, int r) {
    int p = ++idx;
    if (l == r) {
        tr[p] = {l, r, 1};
        return p;
    }
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    tr[p].cnt = tr[tr[p].l].cnt + tr[tr[p].r].cnt;
    return p;
}

int insert(int p, int l, int r, int x) {
    // 每一个版本的线段树都是对上一个版本的更改
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[q].cnt++;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}

int query(int q, int p, int l, int r, int k) {
    // 新版本q和旧版本p的差就是新插入的数据数目
    if (l == r) return r;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}


int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        nums.push_back(a[i]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    root[0] = build(0, nums.size() - 1);
    for (int i = 1; i <= n; ++i) {
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));
    }

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)] << endl;
    }
    return 0;
}