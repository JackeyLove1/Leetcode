/*
回滚莫队的精髓
所以我们就改变一下思路：既然删点难写那么咱们就改变思路：不删点。
但每个问询区间大小不一，无法保持只加点不删点。其实可以保持右端点只增不减，
对于左端每次增点后用暴力把增点数据删除（即回滚）即可
针对左端的数据删除，我们用暴力遍历增点路径，对计数数组进行回退(删掉之前的增点)。
在左端点增点前要拷贝一份当前最大重要度，用于保证在左端增点，回滚后最大重要度不变。
具体处理方式：
1：从第一个分块开始，首先用暴力+回滚处理掉问询区间完全包含在该块内的问询。
2:对于问询左端在第一个分块，问询右端在第二个分块的问询。由于R是递增的，先完成R的增点，
再用暴力＋回滚处理掉其位于第一个分块中的点。

此外要注意到x的范围是1e9，所以要用一次离散化

1. 对原序列进行分块，并对询问按照如下的方式排序：以左端点所在的块升序为第一关键字，
以右端点升序为第二关键字

2. 对于处理所有左端点在块𝑇内的询问，我们先将莫队区间左端点初始化为𝑅[𝑇]+1，
右端点初始化为𝑅[𝑇]，这是一个空区间

3. 对于左右端点在同一个块中的询问，我们直接暴力扫描回答即可。

4. 对于左右端点不在同一个块中的所有询问，由于其右端点升序，我们对右端点只做加点操作，
总共最多加点𝑛次

5. 对于左右端点不在同一个块中的所有询问，其左端点是可能乱序的，
我们每一次从𝑅[𝑇]+1的位置出发，只做加点操作，到达询问位置即可，每一个询问最多加𝑛√次。
回答完询问后，我们撤销本次移动左端点的所有改动，使左端点回到𝑅[𝑇]+1的位置

6. 按照相同的方式处理下一块
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 100010;

int n, m, len;
int w[N], cnt[N];
LL ans[N];
struct Query
{
    int id, l, r;
}q[N];
vector<int> nums;

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

void add(int x, LL& res) // 区间求值操作
{
    cnt[x] ++ ;
    res = max(res, (LL)cnt[x] * nums[x]);
}

int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]), nums.push_back(w[i]);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i ++ )
        w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    sort(q, q + m, cmp);

    for (int x = 0; x < m;)
    {
        int y = x;
        while (y < m && get(q[y].l) == get(q[x].l)) y ++ ; // 找到左端点在同一个块的询问
        int right = get(q[x].l) * len + len - 1; // 找到块的右边界

        // 暴力求块内的询问
        while (x < y && q[x].r <= right)
        {
            LL res = 0;
            int id = q[x].id, l = q[x].l, r = q[x].r;
            for (int k = l; k <= r; k ++ ) add(w[k], res);
            ans[id] = res;
            for (int k = l; k <= r; k ++ ) cnt[w[k]] -- ; // 回滚
            x ++ ;
        }

        // 求块外的询问
        LL res = 0;
        int i = right, j = right + 1;
        while (x < y)
        {
            int id = q[x].id, l = q[x].l, r = q[x].r;
            while (i < r) add(w[ ++ i], res);
            LL backup = res;
            while (j > l) add(w[ -- j], res);
            ans[id] = res;
            while (j < right + 1) cnt[w[j ++ ]] -- ; // 回滚
            res = backup; // 回滚
            x ++ ;
        }
        memset(cnt, 0, sizeof cnt);
    }

    for (int i = 0; i < m; i ++ ) printf("%lld\n", ans[i]);
    return 0;
}
