// 滑动窗口问题

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

const int N = 1e6 + 100;
int q[N];

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;

    for(int i = 0; i < n; i++) cin >> q[i];

    deque<int>d;
    for(int i = 0; i < n; i++){
        // 删除过期节点
        if(!d.empty() && i - k + 1 > d.front()) d.pop_front();
        // 将队列从小到大排列
        while (!d.empty() && q[d.back()] >= q[i]) d.pop_back();
        // 将有效的节点坐标加入
        d.push_back(i);
        // 输出有效值
        if(i >= k - 1) cout << q[d.front()] << " ";
    }
    d.clear();
    cout << endl;
    for(int i = 0; i < n; i++){
        // 删除过期节点
        if(!d.empty() && i - k + 1 > d.front()) d.pop_front();
        // 将队列从大到小排列
        while (!d.empty() && q[d.back()] <= q[i]) d.pop_back();
        // 将有效的节点坐标加入
        d.push_back(i);
        // 输出有效值
        if(i >= k - 1) cout << q[d.front()] << " ";
    }

    return 0;
}