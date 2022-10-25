#include <cstdio>
#define MAXN 15010
#define MAXM 32010
#define lowbit(x) ((x) & (-x))
// 树状数组
int tree[MAXM], ans[MAXN];
void update(int i, int x)
{
    for (; i <= MAXM; i += lowbit(i))
        tree[i] += x;
}
int query(int n)
{
    int ans = 0;
    for (; n; n -= lowbit(n))
        ans += tree[n];
    return ans;
}

int main()
{
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%*d", &x); // 已经排好序了，y坐标可以不要了
        ans[query(x + 1)]++; // 统计
        update(x + 1, 1); // 更新，注意这两行都要+1
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}