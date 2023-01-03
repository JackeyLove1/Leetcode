#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 5e5 + 100;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

struct Node {
    int l, r; // l和r表示这一段的起点和终点
    mutable int v; // v表示这一段上所有元素相同的值是多少

    Node(int l, int r = 0, int v = 0) : l(l), r(r), v(v) {}

    bool operator<(const Node &a) const {
        return l < a.l; // 规定按照每段的左端点排序
    }
};

int n, m;
set<Node> s;

void print() {
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << "l:" << it->l << " r:" << it->r << " v:" << it->v << endl;
    }
}

// 以pos去做切割，找到一个包含pos的区间，把它分成[l,pos-1],[pos,r]两半
// 然后返回[pos, r] 的迭代器
inline set<Node>::iterator split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    int l = it->l, r = it->r, v = it->v;
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
void add(int l, int r, int x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    for (set<Node>::iterator it = itl; it != itr; ++it) {
        it->v += x;
    }
}

// 必须先split(r+1) 然后split(l)
void assign(int l, int r, int x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, x));
}

string query(int l, int r) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    if (itl != s.begin() && itr != s.end()) {
        --itl;
        if (itl->v == itr->v) return "No";
        ++itl;
    }
    int cur = itl->v;
    for (auto it = itl; it != itr; ++it) {
        if (it->v != cur) return "No";
    }
    return "Yes";
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读


int main() {
    fhj();
    cin >> n;
    char c;
    for (int i = 1; i <= n; ++i) {
        cin >> c;
        s.insert(Node(i, i, c - 'A'));
    }
    cin >> m;
    while (m--) {
        char op;
        int l, r;
        cin >> op >> l >> r;
        if (op == 'A') {
            cin >> c;
            assign(l, r, c - 'A');
        } else {
            cout << query(l, r) << endl;
        }
    }
    return 0;
}