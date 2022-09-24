#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 50010, M = 200010, S = 1000010;

int n, m, len;
int w[N], ans[M];
struct Query
{
    int id, l, r;
}q[M];
int cnt[S];

// 分块
int get(int x)
{
    return x / len;
}

// 询问区间排序
// 先按左端点排，再按右端点排
bool cmp(const Query& a, const Query& b)
{
    int i = get(a.l), j = get(b.l); //获得在哪个块
    if (i != j) return i < j; // 块小的在前面
    return a.r < b.r; // 如果在同一个块，按右端点小的在前面
}

// 加入一个数
void add(int x, int& res)
{
    if (!cnt[x]) res ++ ;
    cnt[x] ++ ;
}

// 删除一个数
void del(int x, int& res)
{
    cnt[x] -- ;
    if (!cnt[x]) res -- ;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    scanf("%d", &m);
    len = max(1, (int)sqrt((double)n * n / m)); // 确定块的大小

    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r}; // 插入区间
    }
    sort(q, q + m, cmp);

    // 离线查询
    for (int k = 0, i = 0, j = 1, res = 0; k < m; k ++ )
    {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        // 双指针插入和删除， 先右后左,区间从1开始计数，所以采用这种形式
        while (i < r) add(w[ ++ i], res);
        while (i > r) del(w[i -- ], res);
        while (j < l) del(w[j ++ ], res);
        while (j > l) add(w[ -- j], res);
        ans[id] = res;
    }

/********************************
 void solve() {
  BLOCK_SIZE = int(ceil(pow(n, 0.5)));
  sort(querys, querys + m);
  for (int i = 0; i < m; ++i) {
    const query &q = querys[i];
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(r++, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(--r, -1);
    ans[q.id] = nowAns;
  }
}
 ********************************/
    // 获得答案
    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}

/*
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 50010, M = 200010, S = 1000010;

int n, m, len;
int w[N], ans[M];
struct Query
{
    int id, l, r;
}q[M];
int cnt[S];

int get(int x)
{
    return x / len;
}

bool cmp(const Query& a, const Query& b)
{
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

void add(int x, int& res)
{
    if (!cnt[x]) res ++ ;
    cnt[x] ++ ;
}

void del(int x, int& res)
{
    cnt[x] -- ;
    if (!cnt[x]) res -- ;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    scanf("%d", &m);
    len = max(1, (int)sqrt((double)n * n / m));

    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    sort(q, q + m, cmp);

    for (int k = 0, i = 0, j = 1, res = 0; k < m; k ++ )
    {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(w[ ++ i], res);
        while (i > r) del(w[i -- ], res);
        while (j < l) del(w[j ++ ], res);
        while (j > l) add(w[ -- j], res);
        ans[id] = res;
    }

    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}
*/