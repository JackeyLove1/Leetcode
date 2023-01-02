#include <bits/stdc++.h>

#define int long long
#define lid (tr[id].lson)
#define rid (tr[id].rson)
using namespace std;
struct node {
    int loc[2];
} nd[200005], pr[200005];

struct tree {
    int lson, rson, sz, minm[2], maxm[2];
    node p;
} tr[200005];

int lint[200005], cnt, cqt, tot, rt;

inline void push_up(int id) {
    for (int i = 0; i < 2; i++) {
        tr[id].minm[i] = tr[id].maxm[i] = tr[id].p.loc[i];
        if (lid) {
            tr[id].minm[i] = std::min(tr[id].minm[i], tr[lid].minm[i]);
            tr[id].maxm[i] = std::max(tr[id].maxm[i], tr[lid].maxm[i]);
        }
        if (rid) {
            tr[id].minm[i] = std::min(tr[id].minm[i], tr[rid].minm[i]);
            tr[id].maxm[i] = std::max(tr[id].maxm[i], tr[rid].maxm[i]);
        }
    }
    tr[id].sz = tr[lid].sz + tr[rid].sz + 1;
}

void clear(int id) {
    nd[++cnt] = tr[id].p, lint[++cqt] = id;
    if (lid) clear(lid);
    if (rid) clear(rid);
}

int newnode() {
    if (cqt)return lint[cqt--];
    return ++tot;
}

// compare y
inline bool cmp1(node a, node b) {
    return a.loc[1] < b.loc[1];
}

// compare x
inline bool cmp0(node a, node b) {
    return a.loc[0] < b.loc[0];
}

// d is dimension
int rebuild(int id, int l, int r, int d) {
    if (l > r)return 0;
    id = newnode();
    int mid = (l + r) >> 1;
    std::nth_element(nd + l, nd + mid, nd + r + 1, d ? cmp1 : cmp0);
    tr[id].p = nd[mid];
    lid = rebuild(lid, l, mid - 1, d ^ 1);
    rid = rebuild(rid, mid + 1, r, d ^ 1);
    push_up(id);
    return id;
}

double rate = 0.75;

int push_down(int id, int d) {
    if (tr[lid].sz > tr[id].sz * rate || tr[rid].sz > tr[id].sz * rate) {
        cnt = 0;
        clear(id);
        id = rebuild(id, 1, tr[id].sz, d);
    }
    return id;
}

int insert(int id, int d, node u) {
    if (!id) {
        id = newnode();
        lid = rid = 0, tr[id].p = u;
        push_up(id);
        return id;
    }
    if (u.loc[d] <= tr[id].p.loc[d]) lid = insert(lid, d ^ 1, u);
    else
        rid = insert(rid, d ^ 1, u);
    push_up(id);
    id = push_down(id, d);
    return id;
}

priority_queue<int, vector<int>, greater<int> > q;

inline int dis(node a, node b) {
    return ((a.loc[0] - b.loc[0]) * (a.loc[0] - b.loc[0]) + (a.loc[1] - b.loc[1]) * (a.loc[1] - b.loc[1]));
}

int culc(int id, node x) {
    return max(max(dis(node{tr[id].minm[0], tr[id].minm[1]}, x), dis(node{tr[id].minm[0], tr[id].maxm[1]}, x)),
               max(dis(node{tr[id].maxm[0], tr[id].minm[1]}, x), dis(node{tr[id].maxm[0], tr[id].maxm[1]}, x)));
}

void solve(int id, node x) {
    if (culc(id, x) <= q.top())return;
    if (dis(x, tr[id].p) > q.top()) {
        q.pop();
        q.push(dis(x, tr[id].p));
    }
    if (!rid && !lid)return;
    if (!lid) {
        solve(rid, x);
        return;
    }
    if (!rid) {
        solve(lid, x);
        return;
    }
    if (culc(lid, x) < culc(rid, x))solve(rid, x), solve(lid, x);
    else solve(lid, x), solve(rid, x);
}

int n, k;

signed main() {
    cin >> n >> k;
    k <<= 1;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%lld%lld", &x, &y);
        pr[i] = node{x, y};
        rt = insert(rt, 0, pr[i]);
    }
    for (int i = 1; i <= k; i++)q.push(0);
    for (int i = 1; i <= n; i++) {
        solve(rt, pr[i]);
    }
    cout << q.top();
    return 0;
}