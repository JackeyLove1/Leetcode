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

constexpr int N = 1e6 + 100;
typedef long long LL;
LL a[200001];
map<LL, LL> m;//建立一个数字到出现次数的映射 map<num,times>
//A-B=C --> A-C=B
int main() {
    int n;
    LL c;
    LL ans = 0;
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        m[a[i]]++;
        a[i] -= c;
    }
    for (int i = 1; i <= n; i++) ans += m[a[i]];
    cout << ans << endl;
    return 0;
}