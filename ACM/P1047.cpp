#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

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

constexpr int N = 20;
int L, M;
//变量名称与原题相同
int cnt = 0;
//剩余树的数目
int vis[10000 + 10];

//用来判断树木有没有被访问过
int main() {
    memset(vis, 0, sizeof(vis));//初始化该数组
    cin >> L >> M;//标准输入，不解释
    for (int i = 0; i <= L; i++)
        vis[i] = 0;//从0这个树开始，将这条路上所有的树标记为未访问过
    for (int i = 1; i <= M; i++) {
        int head, tail;//定义区间的头和尾
        cin >> head >> tail;
        for (int j = head; j <= tail; j++)
            if (vis[j] == 0)
                vis[j] = 1;//从这个区间的头和尾开始，将所有区间内的树标记为访问过
    }
    for (int i = 0; i <= L; i++) {
        if (vis[i] == 0)
            cnt++;//计算未被访问过的树的数目
    }
    cout << cnt << endl;
    return 0;
}