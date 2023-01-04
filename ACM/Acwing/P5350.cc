#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
constexpr ll MOD = 1000000007;
constexpr ll MAXN = 300005;

struct Node {
    ll l, r;//l和r表示这一段的起点和终点
    mutable ll v;//v表示这一段上所有元素相同的值是多少

    Node(ll l, ll r = 0, ll v = 0) : l(l), r(r), v(v) {}

    bool operator<(const Node &a) const {
        return l < a.l;//规定按照每段的左端点排序
    }
};

ll n, m;
set<Node> s;

//以pos去做切割，找到一个包含pos的区间，把它分成[l,pos-1],[pos,r]两半
set<Node>::iterator split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    ll l = it->l;
    ll r = it->r;
    ll v = it->v;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    //insert函数返回pair，其中的first是新插入结点的迭代器
    return s.insert(Node(pos, r, v)).first;
}

/*
 * 这里注意必须先计算itr。
 * 比如现在区间是[1,4]，如果要add的是[1,2],如果先split(1)
 * 那么返回的itl是[1,4]，但是下一步计算itr的时候会把这个区间删掉拆成[1,2]和[3,4]
 * 那么itl这个指针就被释放了
 * */
void add(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    for (set<Node>::iterator it = itl; it != itr; ++it) {
        it->v = (it->v + x ) % MOD;
    }
}

void assign(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, x));
}

ll query(ll l, ll r) {
    ll res = 0;
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    for (set<Node>::iterator it = itl; it != itr; ++it) {
        res = (res + it->v) % MOD;
    }
    return res;
}

struct block {
    ll value, len;
};

void copyBlock(ll l1, ll r1, ll l2, ll r2) {
    auto itr = split(r1 + 1), itl = split(l1);
    vector<block> blocks;
    for (auto it = itl; it != itr; ++it) {
        blocks.push_back(block{it->v, it->r - it->l + 1});
    }
    itr = split(r2 + 1), itl = split(l2);
    s.erase(itl, itr);
    for (const auto &block: blocks) {
        s.insert(Node{l2, l2 + block.len - 1, block.value});
        l2 += block.len;
    }
}

void swapBlock(ll l1, ll r1, ll l2, ll r2) {
    auto itr = split(r1 + 1), itl = split(l1);
    vector<block> blocks1;
    for (auto it = itl; it != itr; ++it) {
        blocks1.push_back(block{it->v, it->r - it->l + 1});
    }
    s.erase(itl, itr);
    auto itr2 = split(r2 + 1), itl2 = split(l2);
    vector<block> blocks2;
    for (auto it = itl2; it != itr2; ++it) {
        blocks2.push_back(block{it->v, it->r - it->l + 1});
    }
    s.erase(itl2, itr2);
    for (const auto &block: blocks1) {
        s.insert(Node{l1, l1 + block.len - 1, block.value});
        l1 += block.len;
    }
    for (const auto &block: blocks2) {
        s.insert(Node{l2, l2 + block.len - 1, block.value});
        l2 += block.len;
    }
}

void reverseBlock(ll l, ll r) {
    auto itr = split(r + 1), itl = split(l);
    vector<block> blocks;
    for (auto it = itl; it != itr; ++it) {
        blocks.push_back(block{it->v, it->r - it->l + 1});
    }
    reverse(blocks.begin(), blocks.end());
    s.erase(itl, itr);
    for (const auto &block: blocks) {
        s.insert(Node{l, l + block.len - 1, block.value});
        l += block.len;
    }
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int v;
        cin >> v;
        s.insert(Node(i, i, v));
    }
    while (m--) {
        int op, l1, r1, l2, r2, val;
        cin >> op >> l1 >> r1;
        if (op == 1) {
            cout << query(l1, r1) << endl;
        } else if (op == 2) {
            cin >> val;
            assign(l1, r1, val);
        } else if (op == 3) {
            cin >> val;
            add(l1, r1, val);
        } else if (op == 4) {
            cin >> l2 >> r2;
            copyBlock(l1, r1, l2, r2);
        } else if (op == 5) {
            swapBlock(l1, r1, l2, r2);
        } else {
            reverseBlock(l1, r1);
        }
    }

    return 0;
}