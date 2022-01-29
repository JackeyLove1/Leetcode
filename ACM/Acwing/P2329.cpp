#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int n, m, a[55], b[1100];
int w, l, r, mid, tot, sum[1100];

//w是多余的木材，tot是总共能提供的木材的量，sum是John需要的木材的前缀和
bool dfs(int x, int l) {
    if (tot - w < sum[mid]) return false;
    if (x == 0) return true;
    bool flag = false;
    for (int i = l; i <= n; ++i) {
        if (a[i] >= b[x]) {
            a[i] -= b[x];
            if (a[i] < b[1]) w += a[i]; // waste
            if (b[x - 1] == b[x]) flag = dfs(x - 1, i);
            else flag = dfs(x - 1, 1);
            // 回溯
            a[i] += b[x];
            if (a[i] < b[1]) w -= a[i]; // waste
            if (flag) return true;
        }
    }
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];
    sort(b + 1, b + m + 1);//排序
    for (int i = 1; i <= m; i++) sum[i] = sum[i - 1] + b[i];
    //计算前缀和，注意一定要在排序后计算哦！
    while (sum[m] > tot && m) m--;
    //如果选最短的m根都超出了能提供的木材的范围，则一定不可行
    l = 0, r = m;
    while (l <= r)//二分
    {
        mid = (l + r) / 2;
        if (dfs(mid, 1)) l = mid + 1;
        else r = mid - 1;
    }
    cout << l - 1;
    return 0;
}