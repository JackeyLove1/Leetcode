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

constexpr int N = 110;
int w[N];

inline int cnt(int x) {
    return __builtin_popcount(x);
}

int f[5];

int main() {
    int mod;
    scanf("%d", &mod);
    f[0] = 0;
    f[1] = 1;
    f[2] = 1;//初始化
    for (int i = 1; i; i++) {
        f[2] = f[0];
        f[0] = f[1];
        f[1] = (f[2] + f[1]) % mod;//滚存更新
        if (f[0] % mod == 0 && f[1] % mod == 1) {
            printf("%d", i);
            return 0;
        }//判断结束
    }
}