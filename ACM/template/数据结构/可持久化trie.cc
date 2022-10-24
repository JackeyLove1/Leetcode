#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
// 30w初始数据和30w新增,  而10的7次方小于2的24次方, 再加上根节点, 就是说每个数最多需要25位;
const int N = 600010, M = N * 25;

int n, m;
int s[N]; // 前缀和序列
int tr[M][2];
int max_id[M];  // 用于记录当前根节点版本的最大id范围, 更直白的说就是当前点对应要存的数的在前缀和数组s的位置
int root[N], idx;

// i是第i个插入的数的i, p是上一个插入的数的节点号, q是当前节点号, k是现在取到第k位
void insert(int i, int k, int p, int q)
{
    // 如果记录结束了
    if (k < 0)
    {
        max_id[q] = i;  // 记录当前节点(可能会被后面公用)所能到达的最大范围i
        return;
    }

    // 取出前缀和的二进制表示从右往左数第k位v
    // 需要注意的是, 这个s[i]就是我们要存的东西!!!!!
    int v = s[i] >> k & 1;

    // 如果前一个节点存在当前节点没有的分支, 那就把当前节点的这个空的路径指过去, 这就相当于复制!
    if (p) tr[q][v ^ 1] = tr[p][v ^ 1];

    tr[q][v] = ++idx; // 现在才是正常trie树插入

    // 递归插入下一位二进制, tr[q][v]就是我们本轮插入的新节点
    // 而前面我们只复制了前一轮的不同v方向的路径, v方向的还没动过, 于是放到p里面等下一轮
    // 至于为什么可以放到下一轮, 因为当前q新插入的数字(二进制当前位)是v, 而p的这条路径也是v
    // 所以暂时不需要复制
    insert(i, k - 1, tr[p][v], tr[q][v]);

    // 下面是递归到所有点都插入完成才开始进行的, 所以能把最大max_id递归传递回去
    // 每个点的最大范围用子节点最大的值, 然后还能递归传递回去, 因为当前递归层
    // 的q, 就是上一层的tr[q][v], 观察易知每个节点都会有对应max_id
    max_id[q] = max(max_id[tr[q][0]], max_id[tr[q][1]]);
}

int query(int l, int r, int C)
{
    // 选用合适的root, 就是第r-1个节点作为root(-1已在传参前完成)
    // 然后根据异或的前缀和性质才能保证在r左边
    int p = root[r];

    for (int i = 23; i >= 0; i--)
    {
        // C是s[n] ^ x, 从高位到低位逐位检索二进制每一位上能跟C异或结果最大的数
        int v = C >> i & 1; 
        // 自带判空功能如果没有点, max_id会为-1, 那就肯定不能满足>=l (根据初始化max_id[0] = -1)
        // 如果没有这个初始化, max_id[0] 默认为0, 而当l=0 的时候就会令到p误跳到空节点
        // 而max_id又同时可以限制当前的点是在l r区间内
        // 另外, 如果tr[p][v^1]为空, 那么tr[p][v]就肯定不为空,并在l r区间, 因为根据
        // 插入的代码, 每个节点至少有一条当前s[i]的完整路径
        // 而如果tr[p][v^1]不为空但maxid小于l, 同理也能选取到tr[p][v]
        // printf("max_id[%d]: %d, p: %d, l: %d\n", tr[p][v ^ 1], max_id[tr[p][v ^ 1]], p, l);
        if (max_id[tr[p][v ^ 1]] >= l) p = tr[p][v ^ 1]; 
        else p = tr[p][v];
    }
    return C ^ s[max_id[p]];
}

int main()
{
    scanf("%d%d", &n, &m);
    // 前缀和, 初始化root[0]
    max_id[0] = -1;
    root[0] = ++idx;
    insert(0, 23, 0, root[0]);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] ^ x; // 前缀和序列
        root[i] = ++idx;
        insert(i, 23, root[i - 1], root[i]);
    }

    char op[2];
    int l, r, x;
    while (m--)
    {
        scanf("%s", op);
        if (op[0] == 'A')
        {
            scanf("%d", &x);
            n++;
            s[n] = s[n - 1] ^ x;
            root[n] = ++idx;
            insert(n, 23, root[n - 1], root[n]);
        }
        else
        {
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", query(l - 1, r - 1, s[n] ^ x));
        }
    }
    return 0;
}