#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 100000 + 10;
constexpr double eps = 1e-6;

int n;
double a[N], b[N];

inline bool check(double mid) {
    double s = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i] - mid * b[i] > 0)  // 如果权值大于 0
            s += a[i] - mid * b[i];   // 选这个物品
    return s > 0;
}

int main() {
    fhj();
    // 输入
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    // 二分
    double L = 0, R = 1e9;
    while (R - L > eps) {
        double mid = (L + R) / 2;
        if (check(mid))  // mid 可行，答案比 mid 大
            L = mid;
        else  // mid 不可行，答案比 mid 小
            R = mid;
    }
    // 输出
    printf("%.6lf\n", L);
    return 0;
}