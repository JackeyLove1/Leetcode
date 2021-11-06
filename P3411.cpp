#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>
#include <climits>

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

#define N 1000002
using namespace std;
int n, f[N], a[N], book[N], T[N], ans, len;//book为离散数组
bool v[N];//一个数是否被扫描过
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];//先读入原序列
        book[i] = a[i];
    }
    sort(book + 1, book + 1 + n), len = unique(book + 1, book + 1 + n) - book - 1;//离散数组排序、去重（离散的一部分）
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(book + 1, book + 1 + len, a[i]) - book;//将a[ i ]转换为离散过的数组
        if (!v[a[i]]) f[i] = T[a[i] - 1] + 1;//没有被标记过
        else f[i] = T[a[i]] + 1;//被标记过
        T[a[i]] = f[i], v[a[i]] = 1, ans = max(ans, f[i]);//标记、更新答案、更新T数组
    }
    cout << n - ans;
    return 0;
}