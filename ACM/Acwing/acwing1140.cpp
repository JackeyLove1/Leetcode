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
#include <atomic>
#include <thread>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

constexpr int N = 510;
int g[N][N];//存储图
int dt[N];//存储各个节点到生成树的距离
int st[N];//节点是否被加入到生成树中
int pre[N];//节点的前去节点
int n, m;//n 个节点，m 条边

void prim() {
    memset(dt, 0x3f, sizeof(dt));//初始化距离数组为一个很大的数（10亿左右）
    int res = 0;
    dt[1] = 0;//从 1 号节点开始生成
    for (int i = 0; i < n; i++)//每次循环选出一个点加入到生成树
    {
        int t = -1;
        for (int j = 1; j <= n; j++)//每个节点一次判断
        {
            if (!st[j] && (t == -1 || dt[j] < dt[t]))//如果没有在树中，且到树的距离最短，则选择该点
                t = j;
        }

        st[t] = 1;// 选择该点
        res += dt[t];
        for (int i = 1; i <= n; i++)//更新生成树外的点到生成树的距离
        {
            if (dt[i] > g[t][i] && !st[i])//从 t 到节点 i 的距离小于原来距离，则更新。
            {
                dt[i] = g[t][i];//更新距离
                pre[i] = t;//从 t 到 i 的距离更短，i 的前驱变为 t.
            }
        }
    }
    cout << res << endl;
}

void getPath()//输出各个边
{
    for (int i = n; i > 1; i--)//n 个节点，所以有 n-1 条边。

    {
        cout << i << " " << pre[i] << " " << endl;// i 是节点编号，pre[i] 是 i 节点的前驱节点。他们构成一条边。
    }
}

int main() {
    fhj();
    memset(g, 0x3f, sizeof(g));//各个点之间的距离初始化成很大的数
    cin >> n;//输入节点数和边数
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            cin >> w;
            g[i][j] = min(g[i][j], w);
        }
    }
    prim();//求最下生成树
    //getPath();//输出路径
    return 0;
}