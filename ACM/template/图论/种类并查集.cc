#include <cstdio>
#include <cctype>
#include <algorithm>
int read() //快速读入，可忽略
{
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        ans = (ans << 3) + (ans << 1) + c - '0';
        c = getchar();
    }
    return ans;
}
struct data  //以结构体方式保存便于排序
{
    int a, b, w;
} C[100005];
int cmp(data &a, data &b)
{
    return a.w > b.w;
}
int fa[40005], rank[40005];  //以下为并查集
int find(int a)
{
    return (fa[a] == a) ? a : (fa[a] = find(fa[a]));
}
int query(int a, int b)
{
    return find(a) == find(b);
}
void merge(int a, int b)
{
    int x = find(a), y = find(b);
    if (rank[x] >= rank[y])
        fa[y] = x;
    else
        fa[x] = y;
    if (rank[x] == rank[y] && x != y)
        rank[x]++;
}
void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        rank[i] = 1;
        fa[i] = i;
    }
}
int main()
{
    int n = read(), m = read();
    init(n * 2); //对于罪犯i，i+n为他的敌人
    for (int i = 0; i < m; ++i)
    {
        C[i].a = read();
        C[i].b = read();
        C[i].w = read();
    }
    std::sort(C, C + m, cmp);
    for (int i = 0; i < m; ++i)
    {
        if (query(C[i].a, C[i].b))  //试图把两个已经被标记为“朋友”的人标记为“敌人”
        {
            printf("%d\n", C[i].w); //此时的怒气值就是最大怒气值的最小值
            break;
        }
        merge(C[i].a, C[i].b + n);
        merge(C[i].b, C[i].a + n);
        if (i == m - 1)  //如果循环结束仍无冲突，输出0
            puts("0");
    }
    return 0;
}
