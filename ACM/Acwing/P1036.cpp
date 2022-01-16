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

constexpr int N = 110;
int w[N];

inline int cnt(int x) {
    return __builtin_popcount(x);
}

bool isPrime(int n) {    //返回1表示判断为质数，0为非质数，在此没有进行输入异常检测
    float n_sqrt;
    if (n == 2 || n == 3) return true;
    if (n % 6 != 1 && n % 6 != 5) return false;
    n_sqrt = floor(sqrt((float) n));
    for (int i = 5; i <= n_sqrt; i += 6) {
        if (n % (i) == 0 | n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    int res = 0;
    for (int i = 0; i < (1 << n); ++i) {
        if (cnt(i) == m) {
            int sum = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) sum += w[j];
            }
            if (isPrime(sum)) ++res;
        }
    }
    cout << res << endl;
    return 0;
}