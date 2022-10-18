#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

using namespace std;

typedef long long LL;

const int N = 100010, M = 300010, INF = 0x3f3f3f3f;

int n, m;
struct Edge {
    int a, b, w;
    bool used;
    bool operator< (const Edge &e) const {
        return w < e.w;
    }
}edges[M];
int p[N];
int head[N], e[M], w[M], ne[M], idx;
int depth[N], fa[N][17], d1[N][17], d2[N][17];
// d1[i][j] : 从i这个节点开始向上跳2^j步, 这条路径上的最小边权
// d2 次小边权
int q[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = head[a];
    head[a] = idx ++;
}

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

// 建树,建造出最小生成树
void build() {
    memset(head, -1, sizeof head);
    for (int i = 0; i < m; i ++)
        if (edges[i].used) {
            int a = edges[i].a, b = edges[i].b, w = edges[i].w;
            add(a, b, w);
            add(b, a, w);
        }
}

// 用最近公共祖先来求所有路径离根节点的最大的一条边,和次大的一条边
void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[n] = 1;
    q[0] = n;
    int hh = 0, tt = 0;
    while (hh <= tt) {
        int t = q[hh ++];
        for (int i = head[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;  // bfs更新层次
                q[++ tt] = j;  // 宽度优先
                fa[j][0] = t;  // 更新一下 fa(i, 0);
                d1[j][0] = w[i], d2[j][0] = -INF;  // 更新一下d1, d2
                // 只有一条边不存在次长路

                // 都已经更新到这个点了, 之前路径上的距离也都算出来了
                // 所以都可以更新出d1, d2 fa,
                for (int k = 1; k <= 16; k ++) {  // 开始跳
                    int anc = fa[j][k - 1];  // 这anc是跳一半的位置
                    fa[j][k] = fa[anc][k - 1];  // 求得跳2^k之后的位置

                    // distance存储的是j开始跳一半的数据
                    // d1[j][k - 1] 跳一般的最大边
                    // d2[j][k - 1] 跳一半的次大边
                    // d1[anc][k - 1]  跳另一半的最大边
                    // d2[anc][k - 1]  跳另一半的次大边
                    int distance[4] = {d1[j][k - 1], d2[j][k - 1], 
                                       d1[anc][k - 1], d2[anc][k - 1]};

                    d1[j][k] = d2[j][k] = -INF;  // 整条路径的最大值和次大值先初始化为-INF
                    for (int u = 0; u < 4; u ++) {
                        // 更新一下最大值和次大值
                        int d = distance[u];
                        if (d > d1[j][k]) d2[j][k] = d1[j][k], d1[j][k] = d;
                        else if (d != d1[j][k] && d > d2[j][k]) d2[j][k] = d;
                    }
                }
            }
        }
    }
}

// a -> b w是一条非树边
int lca(int a, int b, int w) {
    static int distance[N * 2];
    int cnt = 0;
    if (depth[a] < depth[b]) swap(a, b);
    // 向上跳, 跳到同层
    for (int k = 16; k >= 0; k --) {
        if (depth[fa[a][k]] >= depth[b]) {
            distance[cnt ++] = d1[a][k];  // 每跳一次,记录一下这路径上的最大值
            distance[cnt ++] = d2[a][k];  // 次大值
            a = fa[a][k];
        }
    }

    // 跳到同一层,但是不是同一个节点的话,就继续跳
    if (a != b) {
        for (int k = 16; k >= 0; k --)
            if (fa[a][k] != fa[b][k]) {  // 把这所有东西都存下来
                distance[cnt ++] = d1[a][k];
                distance[cnt ++] = d2[a][k];
                distance[cnt ++] = d1[b][k];
                distance[cnt ++] = d2[b][k];
                a = fa[a][k], b = fa[b][k];
            }
        // 已经找到公共祖先了,公共祖先就是 fa[a][0] = fa[b][0] = anc
        // 把这边也存下来
        distance[cnt ++] = d1[a][0];
        distance[cnt ++] = d1[b][0];
    }

    // 找到公共祖先的
    int dist1 = -INF, dist2 = -INF;
    for (int i = 0; i < cnt; i ++) {
        int d = distance[i];
        // 这里规定dist1 一定严格大于 dist2 (dist2是严格次小值)
        if (d > dist1) dist2 = dist1, dist1 = d;
        // 如果这里 d = dist 而且 d = dist2, 令dist2 = d的话,就会有 dist1 = dist2
        else if (d != dist1 && d > dist2) dist2 = d;
    }

    if (w > dist1) return w - dist1;  // 看一下这个非树边是否大于dist1, 是的话就替换
    // 返回变大了多少
    // w 一定是 >= dist1 > dist2
    // 如果第一个if不满足, 那一定有 w = dist1
    if (w > dist2) return w - dist2;  // 看一下这个非树边是否大于dist2, 是的话就替换
    // 返回变大了多少
}

LL kruskal() {
    for (int i = 1; i <= n; i ++ ) p[i] = i;
    sort(edges, edges + m);
    LL res = 0;

    for (int i = 0; i < m; i ++) {
        int a = find(edges[i].a), b = find(edges[i].b), w = edges[i].w;
        if (a != b) {
            res += w;
            p[a] = b;
            edges[i].used = true;
        }
    }

    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = {a, b, c};
    }

    LL sum = kruskal();
    build();
    bfs();

    LL res = 1e18;
    for (int i = 0; i < m; i ++) {
        if (!edges[i].used) {  // 枚举一下所有非树边
            int a = edges[i].a, b = edges[i].b, w = edges[i].w;
            res = min(res, sum + lca(a, b, w));  // 看看替换后的结果, 取最小值
        }
    }

    printf("%lld", res);
    return 0;
}