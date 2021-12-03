#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
#define INF 0x3f3f3f3f
int t[10];
int map[40][40];
double dp[300][40];//dp[S][v]:到达城市v，并且剩下的车票集合为S
int main() {
    int n, m, p, a, b, i, x, y, z;
    while (scanf("%d%d%d%d%d", &n, &m, &p, &a, &b) != EOF) {
        if (n == 0 && m == 0 && p == 0 && a == 0 && b == 0)
            break;
        for (i = 0; i < n; ++i)
            scanf("%d", &t[i]);
        memset(map, -1, sizeof(map));//初始化地图
        while (p--) {
            scanf("%d%d%d", &x, &y, &z);
            map[x][y] = map[y][x] = z;
        }
        for (i = 0; i < 1 << n; ++i)
            fill(dp[i] + 1, dp[i] + m + 1, INF);//用足够大的值初始化，注意城市的编号从1到m
        dp[(1 << n) - 1][a] = 0;
        double ans = INF;
        int v, u;
        for (int S = (1 << n) - 1; S >= 0; --S) {
            ans = min(ans, dp[S][b]);
            for (v = 1; v <= m; ++v) {
                for (i = 0; i < n; ++i) {
                    if (S >> i & 1)//表示当前编号为i的车票还没有被用到
                    {
                        for (u = 1; u <= m; ++u) {
                            if (map[v][u] >= 0)
                                dp[S - (1 << i)][u] = min(dp[S - (1 << i)][u], 
                                dp[S][v] + map[v][u] * 1.0 / t[i]);
                        }
                    }
                }
            }
        }
        if (ans == INF)
            printf("Impossible\n");
        else
            printf("%0.3f\n", ans);
    }
    return 0;
}