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

constexpr int N = 1e3 + 100;
int p = 1;
int tr[N * 4];
int nums[N], lazy[N];

inline void build(int n) {
//  维护这么多信息都只需要这么几行，可见维护信息单一时代码应该会短的不像话（压行过的话大概三四行）
    for (; p <= n; p <<= 1); // 求解m -> 使得2^m > n的最小的m
    for (int i = p + 1; i <= p + n; ++i) {
        tr[i] = nums[i - p];
    }
}

inline void change(int x, int d) {
    x = x + p;
    for (tr[x] = d, x >>= 1; x > 0; x >>= 1) {
        tr[x] = max(tr[x << 1], tr[x << 1 | 1]);
    }
}

inline void add(int l, int r, int d) {//区间修改
    for (l = p + l - 1, r = p + r + 1; l ^ 1 ^ r;) { //互为兄弟节点（有同一父亲）时停止
        if (~l & 1)tr[l ^ 1] += d, lazy[l ^ 1] += d;//改值并搭懒标记
        if (r & 1)tr[r ^ 1] += d, lazy[r ^ 1] += d;
        l >>= 1, r >>= 1, tr[l] = max(tr[l << 1], tr[l << 1 | 1]) + lazy[l];//边修改边更新
        tr[r] = max(tr[r << 1], tr[r << 1 | 1]) + lazy[r];
    }
    for (l >>= 1; l > 0; l >>= 1)tr[l] = max(tr[l << 1], tr[l << 1 | 1]) + lazy[l];//最后更新到根
}

inline int sch(int l, int r) {//区间查询最大值
    int resl = 0, resr = 0;//左右两边分别记录，因为两边各自遇到的懒标记不一样
    for (l = p + l - 1, r = p + r + 1; l ^ 1 ^ r;) {
        if (~l & 1)resl = max(resl, tr[l ^ 1]);
        if (r & 1)resr = max(resr, tr[r ^ 1]);
        l >>= 1, r >>= 1, resl += lazy[l], resr += lazy[r];
    }
    resl = max(resl, resr);
    for (l >>= 1; l > 0; l >>= 1)resl += lazy[l];//所有祖先的懒标记都要算上
    return resl;
}

using ll = long long;
int f[N], lz[N];

//f[]是主体，lz[]是懒标记
inline void add(int l, int r, ll d) {//区间加
    int siz = 1;//维护当前层的区间的大小
    for (l = p + l - 1, r = p + r + 1; l ^ 1 ^ r;) {
        if (~l & 1)f[l ^ 1] += d * siz, lz[l ^ 1] += d;
        if (r & 1)f[r ^ 1] += d * siz, lz[r ^ 1] += d;
        l >>= 1, r >>= 1, siz <<= 1;
        f[l] = f[l << 1] + f[l << 1 | 1] + lz[l] * siz;
        f[r] = f[r << 1] + f[r << 1 | 1] + lz[r] * siz;
    }
    for (l >>= 1, siz <<= 1; l; l >>= 1, siz <<= 1)//更新到根
        f[l] = f[l << 1] + f[l << 1 | 1] + lz[l] * siz;
}

inline ll query(int l, int r) {//查询区间和
    int sl = 0, sr = 0, siz = 1;
    ll res = 0;//分别维护左右两边查询的区间总长，以便计算懒标记的贡献
    for (l = p + l - 1, r = p + r + 1; l ^ 1 ^ r;) {
        if (~l & 1)res += f[l ^ 1], sl += siz;
        if (r & 1)res += f[r ^ 1], sr += siz;
        l >>= 1, r >>= 1, siz <<= 1;
        res += lz[l] * sl + lz[r] * sr;//不是你要找的区间，但因为是祖先，所以懒标记要算入贡献
    }
    for (l >>= 1, siz <<= 1, sl += sr; l; l >>= 1, siz <<= 1)
        res += lz[l] * sl;
    return res;
}

/*
// 差分zkw线段树
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

constexpr int N = 1e3 + 100;
int nums[N];
int sum[N], mn[N], mx[N]; // 存储区间和/最小值/最大值
int add[N];

int m = 1; // zkw线段树最底层存储数据的起始位置
inline void build(int n) {
//  维护这么多信息都只需要这么几行，可见维护信息单一时代码应该会短的不像话（压行过的话大概三四行）
    for (; m <= n; m <<= 1); // 求解m -> 使得2^m > n的最小的m
    for (int i = m + 1; i <= m + n; ++i) {
        sum[i] = mn[i] = mx[i] = nums[i - m]; // 将数据插入
    }
    for (int i = m - 1; i; --i) {
        // 使用移位操作代替线段树的递归操作
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        // 以下是可修改zkw线段树版本的操作
        // 将标记永久化
        mn[i] = min(mn[i << 1], mn[i << 1 | 1]),
        mn[i << 1] -= mn[i], mn[i << 1 | 1] -= mn[i];

        mx[i] = max(mx[i << 1], mx[i << 1 | 1]),
        mx[i << 1] -= mx[i], mx[i << 1 | 1] -= mx[i];
    }
}

// 单点修改，将位置x的节点增加A
inline void update_node(int x, int v, int A = 0) {
    // 将x映射到zkw线段树的位置，然后自底向上递归修改
    x += m, mx[x] += v, mn[x] += v;
    for (; x > 1; x >>= 1) { // 自底向上递归操作
        sum[x] += v;
        A = min(mn[x], mn[x ^ 1]);
        mn[x] -= A, mn[x ^ 1] -= A, mn[x >> 1] += A;
        A = max(mx[x], mx[x ^ 1]),
        mx[x] -= A, mx[x ^ 1] -= A, mx[x >> 1] += A;
    }
}


// 区间修改，这里我们假设要将一段区间的每个数加上v，然后维护的信息同上
// 这里的 lc 和 rc 的所代表的含义需要讲一下
// lc 代表左端点所处的节点下有多少长度的区间在更新区间内, rc 同理 ，
// 通俗一点地说，就是 s 和 t 所分别走过的节点中包含的更新过的区间的总长
inline void update_part(int s, int t, int v) {
    int A = 0, lc = 0, rc = 0, len = 1;
    for (s += m - 1, t += m + 1; s ^ t ^ 1; s >>= 1, t >>= 1, len <<= 1) { //在这里的 add 就是标记数组了
        if (s & 1 ^ 1) add[s ^ 1] += v, lc += len, mn[s ^ 1] += v, mx[s ^ 1] += v;
        if (t & 1) add[t ^ 1] += v, rc += len, mn[t ^ 1] += v, mx[t ^ 1] += v;

        sum[s >> 1] += v * lc, sum[t >> 1] += v * rc;

        A = min(mn[s], mn[s ^ 1]), mn[s] -= A, mn[s ^ 1] -= A, mn[s >> 1] += A,
        A = min(mn[t], mn[t ^ 1]), mn[t] -= A, mn[t ^ 1] -= A, mn[t >> 1] += A;

        A = max(mx[s], mx[s ^ 1]), mx[s] -= A, mx[s ^ 1] -= A, mx[s >> 1] += A,
        A = max(mx[t], mx[t ^ 1]), mx[t] -= A, mx[t ^ 1] -= A, mx[t >> 1] += A;
    }
    for (lc += rc; s > 1; s >>= 1) {
        sum[s >> 1] += v * lc;
        A = min(mn[s], mn[s ^ 1]), mn[s] -= A, mn[s ^ 1] -= A, mn[s >> 1] += A,
        A = max(mx[s], mx[s ^ 1]), mx[s] -= A, mx[s ^ 1] -= A, mx[s >> 1] += A;
    }
}

// 单点查询
inline int query_node(int x, int ans = 0) {
    for (x += m; x; x >>= 1) ans += mn[x];
    return ans;
}

// 区间查询
inline int query_sum(int s, int t) {
    int lc = 0, rc = 0, len = 1, ans = 0;
    for (s += m - 1, t += m + 1; s ^ t ^ 1; s >>= 1, t >>= 1, len <<= 1) {
        if (s & 1 ^ 1) ans += sum[s ^ 1] + len * add[s ^ 1], lc += len;
        if (t & 1) ans += sum[t ^ 1] + len * add[t ^ 1], rc += len;

        if (add[s >> 1]) ans += add[s >> 1] * lc;
        if (add[t >> 1]) ans += add[t >> 1] * rc;
    }
    for (lc += rc, s >>= 1; s; s >>= 1)
        if (add[s]) ans += add[s] * lc;
    return ans;
}

inline int query_min(int s, int t, int L = 0, int R = 0, int ans = 0) {
    if (s == t) return query_node(s);  // 单点要特判, 下同
    for (s += m, t += m; s ^ t ^ 1; s >>= 1, t >>= 1) { // 这里 s 和 t 直接加上 m
        L += mn[s], R += mn[t];
        if (s & 1 ^ 1) L = min(L, mn[s ^ 1]);
        if (t & 1) R = min(R, mn[t ^ 1]);
    }
    for (ans = min(L, R), s >>= 1; s; s >>= 1) ans += mn[s];
    return ans;
}

inline int query_max(int s, int t, int L = 0, int R = 0, int ans = 0) {
    if (s == t) return query_node(s);
    for (s += m, t += m; s ^ t ^ 1; s >>= 1, t >>= 1) {
        L += mx[s], R += mx[t];
        if (s & 1 ^ 1) L = max(L, mx[s ^ 1]);
        if (t & 1) R = max(R, mx[t ^ 1]);
    }
    for (ans = max(L, R), s >>= 1; s; s >>= 1) ans += mx[s];
    return ans;
}
*/