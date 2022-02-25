#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

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

constexpr int N = 2e4 + 100;
int n, a[N][2], f[N][2];

inline int dis(int x, int y)//计算距离
{
    return abs(x - y);
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    f[1][0] = dis(a[1][1], 1) + dis(a[1][1], a[1][0]);
    f[1][1] = dis(a[1][1], 1);
    for (int i = 2; i <= n; i++)//状态转移
    {
        f[i][0] = min(f[i - 1][0] + dis(a[i - 1][0], a[i][1]) + dis(a[i][1], a[i][0]),
                      f[i - 1][1] + dis(a[i - 1][1], a[i][1]) + dis(a[i][1], a[i][0])) + 1;
        f[i][1] = min(f[i - 1][0] + dis(a[i - 1][0], a[i][0]) + dis(a[i][0], a[i][1]),
                      f[i - 1][1] + dis(a[i - 1][1], a[i][0]) + dis(a[i][0], a[i][1])) + 1;
    }
    cout << min(f[n][0] + dis(a[n][0], n), f[n][1] + dis(a[n][1], n)) << endl;//最后的答案还要加上到(n,n)的距离
}