#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

const int N = 100100, M = 400100;

int h[N], e[M], ne[M], idx;
int ans[N * 2], cnt;
bool used[M];
int din[N], dout[N];
int n, m, ver;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
// 欧拉回路
void dfs(int u) {
    for (int &i = h[u]; i != -1;) {
        if (used[i]) {  //如果这条边用过了
            i = ne[i];   //删除这条边
            continue;
        }

        used[i] = true;  //标记这条边已使用
        if (ver == 1) used[i ^ 1] = true;   //如果是无向图，那么这条边的反向边也要标记使用过了

        int t;
        if (ver == 1) {
            t = i / 2 + 1;
            if (i & 1) t = -t;  //(0,1) (2,3) (4,5) 奇数编号是返回的边

        } else t = i + 1;

        int j = e[i];
        i = ne[i];
        dfs(j);
        ans[cnt++] = t;
    }
}

int main() {
    scanf("%d%d%d", &ver, &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        if (ver == 1) add(b, a);  //无向边
        din[b]++, dout[a]++;
    }

    if (ver == 1) {
        for (int i = 1; i <= n; i++) {
            if (din[i] + dout[i] & 1) {
                //无向图含欧拉回路的充要条件是每个点的度都为偶数
                puts("NO");
                return 0;
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            if (din[i] != dout[i]) {
                //有向图含欧拉回路的充要条件是每个点的入度等于出度
                puts("NO");
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (~h[i]) {
            dfs(i);
            break;
        }
    }

    if (cnt < m) {
        puts("NO");
        return 0;
    }

    puts("YES");
    for (int i = cnt - 1; i >= 0; --i) {
        cout << ans[i] << " ";
    }
    return 0;
}


/*
// 欧拉路径
#include<bits/stdc++.h>
using namespace std;
int edge[1000][1000];
//为了方便优先访问编号小的节点，这里使用邻接矩阵来存边
//如果使用vector来存图，那还需要对每个节点连接的边进行排序
int ans[1000000];
int degree[1000];//用于储存每个点的度，以求起点
int p=0;
void dfs(int now)
{
    for(int i=1;i<=1000;i++)//顺序寻找可访问的边，优先找编号小的节点
    {
        if(edge[now][i])//若这条边尚未访问过
        {
            edge[now][i]--;//已访问过的边要删去，防止重复访问
            edge[i][now]--;//有向图的话请删去这一行
            dfs(i);
        }
    }
    ans[++p]=now;//将访问的节点储存进答案数组
    //由于递归的特性，这里储存的是逆序过程
}
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;//边的个数
    for(int i=1;i<=n;i++)
    {
        int a,b;
        cin>>a>>b;
        edge[a][b]++;
        edge[b][a]++;//有向图的话删去这行
        degree[a]++,degree[b]++;//两个点的度都+1
    }
    int start=0;
    for(int i=1;i<=1000;i++)
    {
        if(degree[i]%2)//如果找到奇数点
        {
            start=i;//那这个奇数点就作为起点，由于顺序遍历，这个起点编号必定最小
            break;
        }
    }
    if(!start)//如果还没找到奇数点，说明是欧拉回路
    {
        for(int i=1;i<=1000;i++)
            if(degree[i])//寻找最小的有度的点即可
            {
                start=i;
                break;
            }
    }
    dfs(start);//dfs寻找欧拉路
    for(int i=p;i>=1;i--)
        cout<<ans[i];//输出给定的欧拉路
}
*/