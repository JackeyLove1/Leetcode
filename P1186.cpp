#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e6 + 100, INF = 1e9;

int n, m, k;

int q[N];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 0; i < n; i++) cin >> q[i];

    deque<int> d;
    for (int i = 0; i < n; i++) {
        // 删除过期节点
        if (!d.empty() && i - k + 1 > d.front()) d.pop_front();
        // 将队列从小到大排列
        while (!d.empty() && q[d.back()] >= q[i]) d.pop_back();
        // 将有效的节点坐标加入
        d.push_back(i);
        // 输出有效值
        if (i >= k - 1) cout << q[d.front()] << " ";
    }
    d.clear();
    cout << endl;
    for (int i = 0; i < n; i++) {
        // 删除过期节点
        if (!d.empty() && i - k + 1 > d.front()) d.pop_front();
        // 将队列从大到小排列
        while (!d.empty() && q[d.back()] <= q[i]) d.pop_back();
        // 将有效的节点坐标加入
        d.push_back(i);
        // 输出有效值
        if (i >= k - 1) cout << q[d.front()] << " ";
    }

    return 0;
}