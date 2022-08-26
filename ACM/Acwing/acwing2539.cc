#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <atomic>
#include <unistd.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 100010;

int n, m;
struct Node {
    int s[2], p, v;
    int sum, rev;
} tr[N];
int stk[N];

void pushrev(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushup(int x) {
    tr[x].sum = tr[tr[x].s[0]].sum ^ tr[x].v ^ tr[tr[x].s[1]].sum;
}

void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

bool isroot(int x) {
    return tr[tr[x].p].s[0]!= x && tr[tr[x].p].s[1] != x;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r))stk[++top] = r = tr[r].p;
    while (top) pushdown(stk[top--]);
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y)) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void access(int x) {
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x) {
    access(x);
    pushrev(x);
}

int findroot(int x) {
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y) {
    makeroot(x);
    access(y);
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}

void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &tr[i].v);
    while (m--) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 0) {
            split(x, y);
            printf("%d\n", tr[y].sum);
        } else if (t == 1) link(x, y);
        else if (t == 2) cut(x, y);
        else {
            splay(x);
            tr[x].v = y;
            pushup(x);
        }
    }
    return 0;
}