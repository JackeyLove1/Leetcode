#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define LL long long
using namespace std;
const int maxn = 1e3+10;
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
 
int wx[maxn], wy[maxn];  //每个点的顶标值（需要根据二分图处理出来）
int matchx[maxn], matchy[maxn];        //每个点所匹配的点
int visx[maxn], visy[maxn];    //每个点是否加入增广路
int cntx = maxn, cnty = maxn;  //分别是X和Y的点数
int mp[maxn][maxn];  //二分图边的权值
int d;  //边权和顶标最小的差值
 
bool dfs(int u)  //进入DFS的都是X部的点
{
    visx[u] = 1;  //标记进入增广路
    for (int v = 0; v < cnty; v++) {
        if (!visy[v] && mp[u][v] != INF)
        {
            int t = wx[u] + wy[v] - mp[u][v];
            if (t == 0)  // t为0说明是相等子图
            {
                visy[v] = 1;
                if (matchy[v] == -1 || dfs(matchy[v])) {
                    matchx[u] = v;
                    matchy[v] = u;  //进行匹配
                    return true;
                }
            } 
            else if (t > 0)  //此处t一定是大于0，因为顶标之和一定>=边权
            {
                d = min(d, t);  //边权和顶标最小的差值
            }
        }
    }
    return false;
}
 
int KM() {
    memset(matchx, -1, sizeof(matchx));
    memset(matchy, -1, sizeof(matchy));
    memset(wx, 0, sizeof(wx));  // wx的顶标为该点连接的边的最大权值
    memset(wy, 0, sizeof(wy));      // wy的顶标为0
    for (int i = 0; i < cntx; i++)  //预处理出顶标值
    {
        for (int j = 0; j < cnty; j++) {
            if (mp[i][j] == INF) {
                continue;
            }
            wx[i] = max(wx[i], mp[i][j]);
        }
    }
    for (int i = 0; i < cntx; i++)  //枚举X部的点
    {
        while (1) {
            d = INF;
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if (dfs(i)) break;  //已经匹配正确
 
            //还未匹配，将X部的顶标减去d，Y部的顶标加上d
            for (int j = 0; j < cntx; j++)
                if (visx[j]) wx[j] -= d;
            for (int j = 0; j < cnty; j++)
                if (visy[j]) wy[j] += d;
        }
    }
 
    int ans = 0;  //二分图最优匹配权值
    for (int i = 0; i < cntx; i++)
        if (matchx[i] != -1) ans += mp[i][matchx[i]];
    return ans;
}
int n, k;
int main() {
    int result = KM();
    cout << result << endl;
    return 0;
}