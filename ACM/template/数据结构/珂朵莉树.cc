// 把值相同的区间合并成一个结点保存在 set 里面
// 只要是有区间赋值操作的数据结构题都可以用来骗分
// 区间加 区间赋值 求区间第k大值 求区间n次方和
// 可以将数据离线，使用莫对+玛多利树
#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
using ll = long long;

// 珂朵莉树的思想在于随机数据下的区间赋值操作很可能让大量元素变为同一个数
class node {
public:
    int l, r;
    // mutable修饰可以直接修改已经插入set的元素的v值，而不用将该元素取出后重新加入set
    mutable int v;

    explicit node(int l_, int r_, int v_) : l(l_), r(r_), v(v_) {}

    bool operator<(const node &rhs) const {
        return l < rhs.l;
    }
};

set<node> tree;

// 把<l,r,v>断成<l,pos-1,v>和<pos,r,v>：
auto split(ll pos) {
    auto it = tree.lower_bound(node(pos, 0, 0)); // 寻找左端点大于等于pos的第一个节点
    if (it != tree.end() && it->l == pos) // 如果已经存在以pos为左端点的节点，直接返回
        return it;
    it--; // 否则往前数一个节点
    ll l = it->l, r = it->r, v = it->v;
    tree.erase(it); // 删除该节点
    tree.insert(node(l, pos - 1, v)); // 插入<l,pos-1,v>和<pos,r,v>
    return tree.insert(node(pos, r, v)).first; // 返回以pos开头的那个节点的迭代器
    // insert默认返回值是一个pair，第一个成员是我们要的
}

// 区间赋值
void assign(ll l, ll r, ll v) {
    auto end = split(r + 1), begin = split(l); // 顺序不能颠倒，否则可能RE
    tree.erase(begin, end); // 清除一系列节点
    tree.insert(node(l, r, v)); // 插入新的节点
}

// 区间加
void add(ll l, ll r, ll v) {
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        it->v += v;
}

// 区间第K大
ll kth(ll l, ll r, ll k) {
    auto end = split(r + 1);
    vector<pair<ll, ll>> v; // 这个pair里存节点的值和区间长度
    for (auto it = split(l); it != end; it++)
        v.emplace_back(it->v, it->r - it->l + 1);
    sort(v.begin(), v.end()); // 直接按节点的值的大小排下序
    for (int i = 0; i < v.size(); i++) // 然后挨个丢出来，直到丢出k个元素为止
    {
        k -= v[i].second;
        if (k <= 0) return v[i].first;
    }
    return -1;
}

// 区间N次方
ll qpow(ll a, ll b, ll mod) {
    a %= p;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll sum_of_pow(ll l, ll r, ll x, ll y) {
    ll tot = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        tot = (tot + qpow(it->v, x, y) * (it->r - it->l + 1)) % y;
    return tot;
}
