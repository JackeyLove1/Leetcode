#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll MOD = 1000000007;
const ll MAXN = 100005;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

struct Node {
    ll l, r;//l和r表示这一段的起点和终点
    mutable ll v;//v表示这一段上所有元素相同的值是多少

    Node(ll l, ll r = 0, ll v = 0) : l(l), r(r), v(v) {}

    bool operator<(const Node &a) const {
        return l < a.l;//规定按照每段的左端点排序
    }
};

ll n, m, seed, vmax, a[MAXN];
set<Node> s;

// 以pos去做切割，找到一个包含pos的区间，把它分成[l,pos-1],[pos,r]两半
// 然后返回[pos, r] 的迭代器
set<Node>::iterator split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    ll l = it->l, r = it->r, v = it->v;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    //insert函数返回pair，其中的first是新插入结点的迭代器
    return s.insert(Node(pos, r, v)).first;
}

/*
 * 这里注意必须先计算iter
 * 比如现在区间是[1,4]，如果要add的是[1,2],如果先split(1)
 * 那么返回的itl是[1,4]，但是下一步计算iter的时候会把这个区间删掉拆成[1,2]和[3,4]
 * 那么itl这个指针就被释放了
 * */
void add(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    for (set<Node>::iterator it = itl; it != itr; ++it) {
        it->v += x;
    }
}

// 必须先split(r+1) 然后split(l)
void assign(ll l, ll r, ll x) {
    set<Node>::iterator iter = split(r + 1), itl = split(l);
    s.erase(itl, iter);
    s.insert(Node(l, r, x));
}

struct Rank {
    ll num, cnt;

    bool operator<(const Rank &a) const {
        return num < a.num;
    }

    Rank(ll num, ll cnt) : num(num), cnt(cnt) {}
};

ll rnk(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    vector<Rank> v;
    for (set<Node>::iterator i = itl; i != itr; ++i) {
        v.push_back(Rank(i->v, i->r - i->l + 1));
    }
    sort(v.begin(), v.end());
    int i;
    for (i = 0; i < v.size(); ++i) {
        if (v[i].cnt < x) {
            x -= v[i].cnt;
        } else {
            break;
        }
    }
    return v[i].num;
}

ll ksm(ll x, ll y, ll p) {
    ll r = 1;
    ll base = x % p;
    while (y) {
        if (y & 1) {
            r = r * base % p;
        }
        base = base * base % p;
        y >>= 1;
    }
    return r;
}

ll calP(ll l, ll r, ll x, ll y) {
    set<Node>::iterator iter = split(r + 1), itl = split(l);
    ll ans = 0;
    for (set<Node>::iterator i = itl; i != iter; ++i) {
        ans = (ans + ksm(i->v, x, y) * (i->r - i->l + 1) % y) % y;
    }
    return ans;
}

ll rnd() {
    ll ret = seed;
    seed = (seed * 7 + 13) % MOD;
    return ret;
}

int main() {
    fhj();
    cin >> n >> m >> seed >> vmax;
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % vmax) + 1;
        s.insert(Node(i, i, a[i]));
    }
    for (int i = 1; i <= m; ++i) {
        ll op, l, r, x, y;
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        if (op == 3) {
            x = (rnd() % (r - l + 1)) + 1;
        } else {
            x = (rnd() % vmax) + 1;
        }
        if (op == 4) {
            y = (rnd() % vmax) + 1;
        }
        if (op == 1) {
            add(l, r, x);
        } else if (op == 2) {
            assign(l, r, x);
        } else if (op == 3) {
            cout << rnk(l, r, x) << endl;
        } else {
            cout << calP(l, r, x, y) << endl;
        }
    }
    return 0;
}