#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

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

using LL = long long;

const int N = 4;

int n, m;

// 类似于快速幂的写法
void mul(int c[], int a[], int b[][N]) // c <- a * b
{
    static int temp[N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i] = (temp[i] + (LL) a[j] * b[j][i]) % m;

    memcpy(c, temp, sizeof temp);
}

void mul(int c[][N], int a[][N], int b[][N]) // c <- a * b
{
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (LL) a[i][k] * b[k][j]) % m;

    memcpy(c, temp, sizeof temp);
}

int main()
{
    fhj();
    cin >> n >> m;

    // {fn, fn+1, sn, pn}
    // pn = n * sn - tn
    int f1[N][N] = {1, 1, 1, 0};
    int a[N][N] = {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 1},
    };

    int k = n - 1;

    // 快速幂
    while (k)
    {
        if (k & 1) mul(f1, f1, a);  // f1 = f1 * a
        mul(a, a, a);  // a = a * a
        k >>= 1;
    }

    cout << (((LL)n * f1[0][2] - f1[0][3]) % m + m) % m << endl;

    return 0;
}
