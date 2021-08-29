#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
constexpr int N = 1e6 + 100;
int e[N], h[N], ne[N], idx;
int cost[N], d[N], pre[N];// 节点的花费，入度， 上一个节点所用的时间

// 链式前星建图
inline void init() {
    memset(h, -1, sizeof h);
    memset(cost, 0, sizeof cost);
    memset(e, 0, sizeof e);
    memset(d, 0, sizeof d);
    memset(ne, 0, sizeof ne);
    memset(pre, 0, sizeof pre);
    idx = 0;
}

inline void add(int a, int b) { // 添加一条边a -> b
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    ++d[b];// b入度增加
}

int main() {
    ios::sync_with_stdio(false); // C++加快输入输出
    cin.tie(0); // 同上
    int T;// 测试例子个数
    cin >> T;
    while (T--) {
        init();//将存图的数组初始化
        cin >> n;//获得点的个数
        int b;// 终点
        for (int a = 1; a <= n; a++) {// 得到起点
            cin >> cost[a] >> m;
            while (m--) {
                cin >> b;
                add(a, b);
            }
        }
        int time = 0;
        queue<int> q;// 拓扑排序
        for (int i = 1; i <= n; i++) {
            if (!d[i]) {
                q.push(i);// 入度为0的加入
            }
        }
        while (!q.empty()) {
            for (int i = 0, sz = q.size(); i < sz; i++) {
                auto t = q.front();
                q.pop();
                cost[t] += pre[t]; // 上一个节点所用时间和本次所用时间之和就是本次节点用的时间
                for (int j = h[t]; j != -1; j = ne[j]) { //遍历与a相邻的边
                    int k = e[j];
                    pre[k] = max(pre[k], cost[t]); // 更新k节点的上一个节点所用的时间
                    if (--d[k] == 0) { // a -> b, b点的入度为0的话
                        q.push(k);
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            time = max(time, cost[i]); // 得到节点最长用的时间即可
        }
        cout << time << endl;
    }
    return 0;
}