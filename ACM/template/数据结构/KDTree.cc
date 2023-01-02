#include<bits/stdc++.h>

using namespace std;
constexpr int N = 55555, K = 5;
constexpr int INF = 0x3f3f3f3f;

template<typename T>
inline T sqr(T x) {
    return x * x;
}

int k, n, idx;   //k为维数,n为点数
struct point {
    int x[K];

    bool operator<(const point &u) const {
        return x[idx] < u.x[idx];
    }
} po[N];

using tp = pair<double, point>;
priority_queue<tp> pq;

struct kdTree {
    point pt[N << 2];
    int son[N << 2];

    void build(int l, int r, int rt = 1, int dep = 0) {
        if (l > r) return;
        son[rt] = r - l;
        son[rt << 1] = son[rt << 1 | 1] = -1;
        idx = dep % k;
        int mid = (l + r) / 2;
        std::nth_element(po + l, po + mid, po + r + 1);
        pt[rt] = po[mid];
        build(l, mid - 1, rt * 2, dep + 1);
        build(mid + 1, r, rt * 2 + 1, dep + 1);
    }

    void query(point p, int m, int rt = 1, int dep = 0) {
        if (son[rt] == -1) return;
        tp node(0, pt[rt]);
        for (int i = 0; i < k; i++) node.first += sqr(node.second.x[i] - p.x[i]);
        int dim = dep % k, x = rt << 1, y = rt << 1 | 1, fg = 0;
        if (p.x[dim] >= pt[rt].x[dim]) std::swap(x, y);
        if (~son[x]) query(p, m, x, dep + 1);
        if (pq.size() < m) pq.push(node), fg = 1;
        else {
            if (node.first < pq.top().first) pq.pop(), pq.push(node);
            if (sqr(p.x[dim] - pt[rt].x[dim]) < pq.top().first) fg = 1;
        }
        if (~son[y] && fg) query(p, m, y, dep + 1);
    }
} kd;

inline void print(point &p) {
    for (int j = 0; j < k; j++) printf("%d%c", p.x[j], j == k - 1 ? '\n' : ' ');
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) scanf("%d", &po[i].x[j]);
        kd.build(0, n - 1);
        int t, m;
        for (scanf("%d", &t); t--;) {
            point ask;
            for (int j = 0; j < k; j++) scanf("%d", &ask.x[j]);
            scanf("%d", &m);
            kd.query(ask, m);
            printf("the closest %d points are:\n", m);
            point pt[20];
            for (int j = 0; !pq.empty(); j++) pt[j] = pq.top().second, pq.pop();
            for (int j = m - 1; j >= 0; j--) print(pt[j]);
        }
    }
    return 0;
}