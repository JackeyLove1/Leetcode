// 数组模拟单调队列，前缀和
int q[500086], sum[500086];
// 队头，队尾，数字个数，数字限制 
//答案注意有可能是负数
int l, r, n, m, ans = -2147480000; 

int main()
{
    n = Read(), m = Read();
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + Read();
    }
    // 队列初始化
    l = r = 1, q[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        // 如果过时那么弹出队头
        while (l <= r && q[l] < i - m)
            l++;
        // 更新决策
        ans = max(ans, sum[i] - sum[q[l]]);
        // 如果队尾的前缀和大于当前的前缀和
        // 弹出这些前缀和
        while (l <= r && sum[i] <= sum[q[r]])
            r--;
        // 压进当前决策
        q[++r] = i;
    }
    printf("%d\n", ans);
    return 0;
}